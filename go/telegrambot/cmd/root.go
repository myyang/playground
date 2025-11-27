package cmd

import (
	"context"
	"fmt"
	"log"
	"os"
	"os/signal"
	"strings"
	"syscall"
	"time"

	"github.com/myyang/telegrambot/internal/application/service/bot"
	marketservice "github.com/myyang/telegrambot/internal/application/service/market"
	"github.com/myyang/telegrambot/internal/infra/polymarket"
	"github.com/spf13/cobra"
	"github.com/spf13/viper"
)

var rootCmd = &cobra.Command{
	Use:   "telegram-bot",
	Short: "A Telegram Bot for browsing Polymarket markets",
	Long:  `A Telegram bot that allows users to browse active Polymarket prediction markets.`,
}

var startCmd = &cobra.Command{
	Use:   "start",
	Short: "Start the Telegram bot",
	Run: func(cmd *cobra.Command, args []string) {
		token := viper.GetString("telegram.token")
		if token == "" || token == "YOUR_TELEGRAM_BOT_TOKEN" {
			log.Fatal("Telegram token is not configured. Please set it in config.yaml or via environment variables.")
		}

		polymarketBaseURL := viper.GetString("polymarket.base_url")
		polymarketClient := polymarket.NewClient(polymarketBaseURL)

		cacheTTL := viper.GetDuration("polymarket.cache_ttl") * time.Second
		if cacheTTL == 0 {
			cacheTTL = 5 * time.Minute
		}
		fetchLimit := viper.GetInt("polymarket.fetch_limit")
		if fetchLimit == 0 {
			fetchLimit = 50
		}
		marketCache := marketservice.NewCache(polymarketClient, cacheTTL, fetchLimit)

		webAppURL := viper.GetString("polymarket.web_app_url")
		botService := bot.NewService(marketCache, webAppURL)

		ctx, cancel := signal.NotifyContext(context.Background(), syscall.SIGINT, syscall.SIGTERM)
		defer cancel()

		log.Println("Starting bot...")
		if err := botService.Start(ctx, token); err != nil {
			log.Fatalf("Bot encountered an error: %v", err)
		}
		log.Println("Bot stopped gracefully.")
	},
}

func init() {
	cobra.OnInitialize(initConfig)
	rootCmd.AddCommand(startCmd)
}

func initConfig() {
	viper.SetConfigName("config")
	viper.SetConfigType("yaml")
	viper.AddConfigPath(".")

	viper.SetEnvPrefix("TELEGRAM")
	viper.SetEnvKeyReplacer(strings.NewReplacer(".", "_"))
	viper.AutomaticEnv()

	viper.SetDefault("polymarket.base_url", "https://gamma-api.polymarket.com")
	viper.SetDefault("polymarket.cache_ttl", 300)
	viper.SetDefault("polymarket.fetch_limit", 50)
	viper.SetDefault("polymarket.web_app_url", "https://polymarket.com")

	if err := viper.ReadInConfig(); err != nil {
		if _, ok := err.(viper.ConfigFileNotFoundError); !ok {
			log.Fatalf("Error reading config file: %s \n", err)
		}
	}
}

func Execute() {
	if err := rootCmd.Execute(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}
