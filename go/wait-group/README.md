# WaitGroup Concurrency Patterns

Demonstrates Go concurrency patterns with `sync.WaitGroup`.

## Features

- Multiple workers with different deadlines
- Context-based cancellation
- Worker respawn mechanism (odd-indexed workers respawn after deadline)
- Ticker-based periodic operations

## Usage

```bash
go run main.go
```

## Concepts Demonstrated

- `sync.WaitGroup` for goroutine synchronization
- `context.WithDeadline` for timeout control
- `time.Ticker` for periodic tasks
- Worker lifecycle management and respawn
