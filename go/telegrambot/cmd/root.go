package cmd

import (
	"context"
	"fmt"
	"log"
	"os"
	"os/signal"
	"strings"
	"syscall"

	"github.com/myyang/telegrambot/internal/application/service/bot"
	"github.com/spf13/cobra"
	"github.com/spf13/viper"
)

var rootCmd = &cobra.Command{
	Use:   "telegram-bot",
	Short: "A simple Telegram Echo Bot",
	Long:  `A proof-of-concept Telegram bot that echoes back any message it receives.`,
}

var startCmd = &cobra.Command{
	Use:   "start",
	Short: "Start the Telegram bot",
	Run: func(cmd *cobra.Command, args []string) {
		token := viper.GetString("telegram.token")
		if token == "" || token == "YOUR_TELEGRAM_BOT_TOKEN" {
			log.Fatal("Telegram token is not configured. Please set it in config.yaml or via environment variables.")
		}

		ctx, cancel := signal.NotifyContext(context.Background(), syscall.SIGINT, syscall.SIGTERM)
		defer cancel()

		log.Println("Starting bot...")
		if err := bot.StartBot(ctx, token); err != nil {
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

	// Allow reading from environment variables
	viper.SetEnvPrefix("TELEGRAM")
	viper.SetEnvKeyReplacer(strings.NewReplacer(".", "_"))
	viper.AutomaticEnv()

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
