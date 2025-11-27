package bot

import (
	"context"
	"fmt"
	"log"
	"strconv"
	"strings"

	"github.com/go-telegram/bot"
	"github.com/go-telegram/bot/models"

	domain "github.com/myyang/telegrambot/internal/domain/market"
)

const (
	CallbackPrefixPrev    = "market_prev_"
	CallbackPrefixNext    = "market_next_"
	CallbackPrefixConfirm = "market_confirm_"
)

// handleHelpCommand handles the /help command
func (s *Service) handleHelpCommand(ctx context.Context, b *bot.Bot, update *models.Update) {
	if update.Message == nil {
		return
	}

	text := `🤖 <b>Telegram Bot Commands</b>

/help - Show this help message
/markets - Browse Polymarket markets with inline navigation

Use the buttons below to visit Polymarket for full experience.`

	b.SendMessage(ctx, &bot.SendMessageParams{
		ChatID:      update.Message.Chat.ID,
		Text:        text,
		ParseMode:   models.ParseModeHTML,
		ReplyMarkup: buildVisitButtonMarkup(s.webAppURL),
	})
}

// handleMarketsCommand handles the /markets command
func (s *Service) handleMarketsCommand(ctx context.Context, b *bot.Bot, update *models.Update) {
	if update.Message == nil {
		return
	}

	chatID := update.Message.Chat.ID

	market, err := s.marketCache.GetMarketByIndex(ctx, 0)
	if err != nil {
		log.Printf("Failed to get market: %v", err)
		b.SendMessage(ctx, &bot.SendMessageParams{
			ChatID: chatID,
			Text:   "Failed to retrieve Markets data. Please try again later.",
		})
		return
	}

	total, _ := s.marketCache.Count(ctx)

	b.SendMessage(ctx, &bot.SendMessageParams{
		ChatID:      chatID,
		Text:        buildMarketMessage(market, 0, total),
		ParseMode:   models.ParseModeHTML,
		ReplyMarkup: buildNavigationKeyboard(0, total, s.webAppURL),
	})
}

// handleMarketNavigation handles navigation button clicks
func (s *Service) handleMarketNavigation(ctx context.Context, b *bot.Bot, update *models.Update) {
	if update.CallbackQuery == nil {
		return
	}

	b.AnswerCallbackQuery(ctx, &bot.AnswerCallbackQueryParams{
		CallbackQueryID: update.CallbackQuery.ID,
	})

	data := update.CallbackQuery.Data
	chatID := update.CallbackQuery.Message.Message.Chat.ID
	messageID := update.CallbackQuery.Message.Message.ID

	var index int
	var err error

	switch {
	case strings.HasPrefix(data, CallbackPrefixPrev):
		indexStr := strings.TrimPrefix(data, CallbackPrefixPrev)
		index, err = strconv.Atoi(indexStr)
		if err != nil {
			log.Printf("Invalid callback data: %s", data)
			return
		}
		index--

	case strings.HasPrefix(data, CallbackPrefixNext):
		indexStr := strings.TrimPrefix(data, CallbackPrefixNext)
		index, err = strconv.Atoi(indexStr)
		if err != nil {
			log.Printf("Invalid callback data: %s", data)
			return
		}
		index++

	default:
		return
	}

	total, _ := s.marketCache.Count(ctx)

	if index < 0 {
		index = total - 1
	}
	if index >= total {
		index = 0
	}

	market, err := s.marketCache.GetMarketByIndex(ctx, index)
	if err != nil {
		log.Printf("Failed to get market at index %d: %v", index, err)
		return
	}

	b.EditMessageText(ctx, &bot.EditMessageTextParams{
		ChatID:      chatID,
		MessageID:   messageID,
		Text:        buildMarketMessage(market, index, total),
		ParseMode:   models.ParseModeHTML,
		ReplyMarkup: buildNavigationKeyboard(index, total, s.webAppURL),
	})
}

// buildMarketMessage formats the market information
func buildMarketMessage(m *domain.Market, index, total int) string {
	marketURL := m.WebURL()
	questionLink := fmt.Sprintf(`<a href="%s"><b>%s</b></a>`, marketURL, m.Question)
	return fmt.Sprintf(
		`<b>Polymarket</b> [%d/%d]

%s

📅 End Date: %s`,
		index+1, total,
		questionLink,
		formatEndDate(m.EndDate),
	)
}

// formatEndDate formats the ISO date string for display
func formatEndDate(endDate string) string {
	if endDate == "" {
		return "Not set"
	}
	if len(endDate) >= 10 {
		return endDate[:10]
	}
	return endDate
}

// buildNavigationKeyboard creates the inline keyboard with navigation buttons
func buildNavigationKeyboard(index, total int, webAppURL string) *models.InlineKeyboardMarkup {
	currentIndexStr := strconv.Itoa(index)

	buttons := [][]models.InlineKeyboardButton{
		{
			{Text: "Prev", CallbackData: CallbackPrefixPrev + currentIndexStr},
			{Text: "Next", CallbackData: CallbackPrefixNext + currentIndexStr},
		},
	}

	if webAppURL != "" {
		buttons = append(buttons, []models.InlineKeyboardButton{
			{Text: "Visit Polymarket", URL: webAppURL},
		})
	}

	return &models.InlineKeyboardMarkup{InlineKeyboard: buttons}
}

func buildVisitButtonMarkup(webAppURL string) *models.InlineKeyboardMarkup {
	if webAppURL == "" {
		return nil
	}
	return &models.InlineKeyboardMarkup{
		InlineKeyboard: [][]models.InlineKeyboardButton{
			{
				{Text: "Visit Polymarket", URL: webAppURL},
			},
		},
	}
}
