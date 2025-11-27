# 專案目標

建立一個簡單的 Go Telegram Echo Bot 作為概念驗證 (POC)。

# 技術棧與函式庫

*   **語言**: Go
*   **Telegram Bot 框架**: `github.com/go-telegram/bot`
*   **CLI 框架**: `github.com/spf13/cobra`
*   **設定管理**: `github.com/spf13/viper`

# 專案架構

採用 DDD (Domain-Driven Design) 架構風格。

```
.
├── AGENTS.md         # 專案開發指引與紀錄
├── go.mod            # Go 模組依賴
├── config.yaml       # 設定檔
├── cmd/              # 程式進入點 (Cobra commands)
│   └── root.go
├── internal/         # 內部實作邏輯 (DDD)
│   ├── application/  # 應用層
│   │   └── service/
│   │       ├── bot/
│   │       │   ├── bot.go      # Bot 服務實作
│   │       │   └── handlers.go # Bot 指令處理
│   │       └── market/
│   │           └── cache.go    # Market 快取服務
│   ├── domain/       # 領域層
│   │   └── market/
│   │       └── market.go       # Market 領域模型
│   └── infra/        # 基礎設施層
│       └── polymarket/
│           └── client.go       # Polymarket API Client
└── main.go           # 主程式進入點
```

# 功能需求

1.  **Echo 功能**: Bot 需能回應使用者傳送的相同文字訊息。
2.  **設定管理**:
    *   使用 `viper` 來管理設定。
    *   Telegram Bot Token 必須可透過設定檔或環境變數傳入，不能寫死在程式碼中。
3.  **CLI 介面**:
    *   使用 `cobra` 建立一個啟動 bot 的指令 (例如 `start`)。
    *   程式應透過 `go run main.go start` 的方式啟動。

# 新增功能 - Polymarket Markets 瀏覽

## 指令
- `/help` - 顯示可用指令與功能說明
- `/markets` - 開始瀏覽 Polymarket 上的活躍預測市場

## 按鈕操作
- `Prev` - 瀏覽上一個市場
- `Next` - 瀏覽下一個市場
- `Visit Polymarket` - 直接開啟 Polymarket 網站或 Mini App 入口

**注意**：市場標題本身是可點擊的連結，點擊後會直接跳轉到該市場的 Polymarket 頁面。

## 設定
在 `config.yaml` 中可設定：
- `polymarket.base_url` - Polymarket API 基礎 URL (預設: https://gamma-api.polymarket.com)
- `polymarket.cache_ttl` - 快取有效期間，單位秒 (預設: 300)
- `polymarket.fetch_limit` - 每次取得的 market 數量 (預設: 50)
- `polymarket.web_app_url` - Telegram Mini App 入口 URL (預設: https://polymarket.com)

# 參考資料

*   Telegram Bot Features: https://core.telegram.org/bots/features
*   Telegram Bot API: https://core.telegram.org/bots/api
*   Polymarket Gamma API: https://gamma-api.polymarket.com
