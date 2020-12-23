package main

import (
	"context"
	"log"
	"sync"
	"time"
)

func worker(ctx context.Context, idx int, wg *sync.WaitGroup) {
	defer wg.Done()

	ticker := time.NewTicker(time.Second * 1)
	deadline := time.NewTimer(time.Second * time.Duration((idx/2+1)*10))

	log.Printf("worker %v: started\n", idx)
	defer log.Printf("worker %v: exited\n", idx)
LOOP:
	for {
		select {
		case <-ctx.Done():
			return
		case <-ticker.C:
			log.Printf("worker: %v: tick\n", idx)
		case <-deadline.C:
			log.Printf("worker: %v: deadline\n", idx)
			break LOOP
		}
	}

	if (idx & 1) == 0 {
		return
	}

	log.Printf("worker %v: respawn...\n", idx)
	wg.Add(1)
	go worker(ctx, idx, wg)
}

func main() {
	var wg sync.WaitGroup
	ctx, cancel := context.WithDeadline(
		context.Background(), time.Now().Add(23*time.Second),
	)
	defer cancel()

	n := 5
	wg.Add(5)
	for i := 0; i < n; i++ {
		go worker(ctx, i, &wg)
	}

	wg.Wait()
	log.Printf("main exited\n")
}
