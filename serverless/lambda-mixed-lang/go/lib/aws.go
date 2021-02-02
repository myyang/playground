package lib

import (
	"github.com/aws/aws-sdk-go/aws"
	"github.com/aws/aws-sdk-go/aws/credentials"
	"github.com/aws/aws-sdk-go/aws/session"
	"github.com/aws/aws-sdk-go/service/dynamodb"
)

// NewAWSConfig returns prodect default config
func NewAWSConfig() (cfg *aws.Config) {
	return &aws.Config{
		Credentials: credentials.NewStaticCredentials(
			"test-key", "test-secret", "",
		),
		Region:   aws.String("us-west-2a"),
		Endpoint: aws.String("http://10.33.136.36:4566"),
	}
}

// NewDynamoDB retruns dynamodb instance
func NewDynamoDB(cfg *aws.Config) *dynamodb.DynamoDB {
	return dynamodb.New(session.New(cfg))
}
