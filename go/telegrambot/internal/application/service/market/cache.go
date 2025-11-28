package market

import (
	"context"
	"fmt"
	"sync"
	"time"

	domain "github.com/myyang/telegrambot/internal/domain/market"
	"github.com/myyang/telegrambot/internal/infra/polymarket"
)

type Cache struct {
	client    *polymarket.Client
	markets   []domain.Market
	updatedAt time.Time
	ttl       time.Duration
	mu        sync.RWMutex
	limit     int
}

func NewCache(client *polymarket.Client, ttl time.Duration, limit int) *Cache {
	return &Cache{
		client: client,
		ttl:    ttl,
		limit:  limit,
	}
}

func (c *Cache) isExpired() bool {
	return time.Since(c.updatedAt) > c.ttl
}

func (c *Cache) GetMarkets(ctx context.Context) ([]domain.Market, error) {
	c.mu.RLock()
	if !c.isExpired() && len(c.markets) > 0 {
		markets := c.markets
		c.mu.RUnlock()
		return markets, nil
	}
	c.mu.RUnlock()

	c.mu.Lock()
	defer c.mu.Unlock()

	// Double-check after acquiring write lock
	if !c.isExpired() && len(c.markets) > 0 {
		return c.markets, nil
	}

	markets, err := c.client.GetMarkets(ctx, c.limit)
	if err != nil {
		return nil, fmt.Errorf("failed to fetch markets: %w", err)
	}

	c.markets = markets
	c.updatedAt = time.Now()
	return c.markets, nil
}

func (c *Cache) GetMarketByIndex(ctx context.Context, index int) (*domain.Market, error) {
	markets, err := c.GetMarkets(ctx)
	if err != nil {
		return nil, err
	}

	if index < 0 || index >= len(markets) {
		return nil, fmt.Errorf("index out of range: %d (total: %d)", index, len(markets))
	}

	return &markets[index], nil
}

func (c *Cache) Count(ctx context.Context) (int, error) {
	markets, err := c.GetMarkets(ctx)
	if err != nil {
		return 0, err
	}
	return len(markets), nil
}
