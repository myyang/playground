package main

import (
	"log"
	"os"

	stripe "github.com/stripe/stripe-go/v72"
	"github.com/stripe/stripe-go/v72/client"
)

func main() {
	sc := &client.API{}
	sc.Init(os.Getenv("STRIPE_SECRET_KEY"), nil)

	it := sc.Products.List(&stripe.ProductListParams{})
	for it.Next() {
		log.Printf("product: %+v\n", it.Product())
	}
}
