package main

import (
	"bytes"
	"context"
	"encoding/json"
	"time"

	"github.com/aws/aws-lambda-go/events"
	"github.com/aws/aws-lambda-go/lambda"
	"github.com/aws/aws-lambda-go/lambdacontext"
	"github.com/aws/aws-sdk-go/aws"
	"github.com/aws/aws-sdk-go/service/dynamodb"

	"github.com/myyang/playground/serverless/lambda-mixed-lang/go/lib"
)

// Response is of type APIGatewayProxyResponse since we're leveraging the
// AWS Lambda Proxy Request functionality (default behavior)
//
// https://serverless.com/framework/docs/providers/aws/events/apigateway/#lambda-proxy-integration
type Response events.APIGatewayProxyResponse

const dbTSKey = "request_ts"

// Handler is our lambda handler invoked by the `lambda.Start` function call
func Handler(ctx context.Context, e events.APIGatewayCustomAuthorizerRequest) (Response, error) {
	ts := time.Now().Format(time.RFC3339)

	lambdaCtx, ok := lambdacontext.FromContext(ctx)
	if !ok {
		lambdaCtx = &lambdacontext.LambdaContext{
			AwsRequestID:       "assign-in-handler-" + ts,
			InvokedFunctionArn: "assign-in-handler-" + ts,
		}
	}

	db := lib.NewDynamoDB(lib.NewAWSConfig())

	_, err := db.PutItem(&dynamodb.PutItemInput{
		TableName: aws.String("serverless_test_db"),
		Item: map[string]*dynamodb.AttributeValue{
			dbTSKey: &dynamodb.AttributeValue{S: aws.String(ts)},
		},
	})
	if err != nil {
		return Response{StatusCode: 500, Body: "Dynamodb error: " + err.Error()}, err
	}

	body, err := json.Marshal(map[string]interface{}{
		"message": "Go Serverless v1.1! Your function executed successfully!",
		"debug": map[string]interface{}{
			"db_time":      ts,
			"request_id":   lambdaCtx.AwsRequestID,
			"function_arn": lambdaCtx.InvokedFunctionArn,
			"auth_request": e,
		},
	})
	if err != nil {
		return Response{StatusCode: 500, Body: "marshal json error"}, err
	}

	var buf bytes.Buffer
	json.HTMLEscape(&buf, body)

	resp := Response{
		StatusCode:      200,
		IsBase64Encoded: false,
		Body:            buf.String(),
		Headers: map[string]string{
			"Content-Type":           "application/json",
			"X-MyCompany-Func-Reply": "world-handler",
		},
	}

	return resp, nil
}

func main() {
	lambda.Start(Handler)
}
