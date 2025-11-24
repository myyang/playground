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
├── cmd/              # 程式進入點 (Cobra commands)
│   └── root.go
├── internal/         # 內部實作邏輯 (DDD)
│   ├── application/  # 應用層
│   │   └── service/
│   │       └── bot/
│   │           └── bot.go # Bot 服務實作
│   ├── domain/       # 領域層 (暫時為空)
│   └── infra/        # 基礎設施層 (暫時為空)
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

# 參考資料

*   Telegram Bot Features: https://core.telegram.org/bots/features
*   Telegram Bot API: https://core.telegram.org/bots/api