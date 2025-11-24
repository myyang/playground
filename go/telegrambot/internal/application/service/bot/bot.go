package bot

import (
	"context"
	"fmt"
	"log"

	"github.com/go-telegram/bot"
	"github.com/go-telegram/bot/models"
)

// StartBot initializes and starts the Telegram bot.
// It blocks until the context is canceled.
func StartBot(ctx context.Context, token string) error {
	opts := []bot.Option{
		bot.WithDefaultHandler(handler),
	}

	b, err := bot.New(token, opts...)
	if err != nil {
		return fmt.Errorf("failed to create bot: %w", err)
	}

	// Start the bot in the background.
	go func() {
		b.Start(ctx)
	}()

	log.Println("Bot is up and running. Waiting for messages...")

	// Wait for the context to be canceled (e.g., by SIGINT).
	<-ctx.Done()

	return nil
}

// handler is the function that processes incoming updates.
func handler(ctx context.Context, b *bot.Bot, update *models.Update) {
	// We only handle incoming text messages.
	if update.Message == nil || update.Message.Text == "" {
		return
	}

	chatID := update.Message.Chat.ID
	receivedText := update.Message.Text

	log.Printf("Received a message from chat ID %d: %s", chatID, receivedText)

	// Echo the message back.
	_, err := b.SendMessage(ctx, &bot.SendMessageParams{
		ChatID: chatID,
		Text:   receivedText,
	})
	if err != nil {
		log.Printf("Failed to send message to chat ID %d: %v", chatID, err)
	}
}
