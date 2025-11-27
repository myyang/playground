package bot

import (
	"context"
	"fmt"
	"log"

	"github.com/go-telegram/bot"
	"github.com/go-telegram/bot/models"

	marketservice "github.com/myyang/telegrambot/internal/application/service/market"
)

// Service represents the bot service with all dependencies
type Service struct {
	marketCache *marketservice.Cache
	webAppURL   string
}

// NewService creates a new bot service
func NewService(marketCache *marketservice.Cache, webAppURL string) *Service {
	return &Service{
		marketCache: marketCache,
		webAppURL:   webAppURL,
	}
}

// Start initializes and starts the Telegram bot
func (s *Service) Start(ctx context.Context, token string) error {
	opts := []bot.Option{
		bot.WithDefaultHandler(s.echoHandler),
		bot.WithMessageTextHandler("help", bot.MatchTypeCommand, s.handleHelpCommand),
		bot.WithMessageTextHandler("markets", bot.MatchTypeCommand, s.handleMarketsCommand),
		bot.WithCallbackQueryDataHandler("market_", bot.MatchTypePrefix, s.handleMarketNavigation),
	}

	b, err := bot.New(token, opts...)
	if err != nil {
		return fmt.Errorf("failed to create bot: %w", err)
	}

	if err := s.registerCommands(ctx, b); err != nil {
		log.Printf("failed to register bot commands: %v", err)
	}

	go func() {
		b.Start(ctx)
	}()

	log.Println("Bot is up and running. Waiting for messages...")
	log.Println("Available commands: /markets - Browse Polymarket markets")

	<-ctx.Done()
	return nil
}

// echoHandler echoes back the received message (original functionality)
func (s *Service) echoHandler(ctx context.Context, b *bot.Bot, update *models.Update) {
	if update.Message == nil || update.Message.Text == "" {
		return
	}

	if len(update.Message.Text) > 0 && update.Message.Text[0] == '/' {
		return
	}

	chatID := update.Message.Chat.ID
	receivedText := update.Message.Text

	log.Printf("Received a message from chat ID %d: %s", chatID, receivedText)

	_, err := b.SendMessage(ctx, &bot.SendMessageParams{
		ChatID: chatID,
		Text:   receivedText,
	})
	if err != nil {
		log.Printf("Failed to send message to chat ID %d: %v", chatID, err)
	}
}

func (s *Service) registerCommands(ctx context.Context, b *bot.Bot) error {
	commands := []models.BotCommand{
		{
			Command:     "help",
			Description: "List available commands",
		},
		{
			Command:     "markets",
			Description: "Browse Polymarket markets",
		},
	}

	_, err := b.SetMyCommands(ctx, &bot.SetMyCommandsParams{
		Commands: commands,
	})
	return err
}
