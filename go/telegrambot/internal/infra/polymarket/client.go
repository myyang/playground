package polymarket

import (
	"context"
	"encoding/json"
	"fmt"
	"net/http"
	"net/url"
	"strconv"
	"time"

	"github.com/myyang/telegrambot/internal/domain/market"
)

const DefaultBaseURL = "https://gamma-api.polymarket.com"

type Client struct {
	baseURL    string
	httpClient *http.Client
}

func NewClient(baseURL string) *Client {
	if baseURL == "" {
		baseURL = DefaultBaseURL
	}
	return &Client{
		baseURL: baseURL,
		httpClient: &http.Client{
			Timeout: 30 * time.Second,
		},
	}
}

// APIEvent represents the event structure in the API response
type APIEvent struct {
	ID   string `json:"id"`
	Slug string `json:"slug"`
}

// APIMarket represents the raw API response structure from Gamma API
type APIMarket struct {
	ID          string     `json:"id"`
	Question    string     `json:"question"`
	Description string     `json:"description"`
	Slug        string     `json:"slug"`
	EndDate     string     `json:"endDate"`
	Active      bool       `json:"active"`
	Closed      bool       `json:"closed"`
	Image       string     `json:"image"`
	Events      []APIEvent `json:"events"`
}

func (c *Client) GetMarkets(ctx context.Context, limit int) ([]market.Market, error) {
	u, _ := url.Parse(c.baseURL + "/markets")
	q := u.Query()
	q.Set("limit", strconv.Itoa(limit))
	q.Set("active", "true")
	q.Set("closed", "false")
	u.RawQuery = q.Encode()

	req, err := http.NewRequestWithContext(ctx, http.MethodGet, u.String(), nil)
	if err != nil {
		return nil, fmt.Errorf("failed to create request: %w", err)
	}

	resp, err := c.httpClient.Do(req)
	if err != nil {
		return nil, fmt.Errorf("failed to fetch markets: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return nil, fmt.Errorf("unexpected status code: %d", resp.StatusCode)
	}

	var apiMarkets []APIMarket
	if err := json.NewDecoder(resp.Body).Decode(&apiMarkets); err != nil {
		return nil, fmt.Errorf("failed to decode response: %w", err)
	}

	markets := make([]market.Market, 0, len(apiMarkets))
	for _, m := range apiMarkets {
		eventSlug := m.Slug
		if len(m.Events) > 0 && m.Events[0].Slug != "" {
			eventSlug = m.Events[0].Slug
		}

		markets = append(markets, market.Market{
			ID:          m.ID,
			Question:    m.Question,
			Description: m.Description,
			Slug:        m.Slug,
			EventSlug:   eventSlug,
			EndDate:     m.EndDate,
			Active:      m.Active,
			Closed:      m.Closed,
			Image:       m.Image,
		})
	}

	return markets, nil
}
