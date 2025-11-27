package market

// Market represents a Polymarket prediction market
type Market struct {
	ID          string `json:"id"`
	Question    string `json:"question"`
	Description string `json:"description"`
	Slug        string `json:"slug"`
	EventSlug   string `json:"event_slug"`
	EndDate     string `json:"endDate"`
	Active      bool   `json:"active"`
	Closed      bool   `json:"closed"`
	Image       string `json:"image"`
}

// WebURL returns the Polymarket web URL for this market
func (m *Market) WebURL() string {
	if m.EventSlug != "" {
		return "https://polymarket.com/event/" + m.EventSlug
	}
	return "https://polymarket.com/event/" + m.Slug
}
