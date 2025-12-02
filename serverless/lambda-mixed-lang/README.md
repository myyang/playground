# Lambda Mixed Language

AWS Lambda functions with multiple languages using Serverless Framework.

## Languages

| Language | Handler | Endpoint |
|----------|---------|----------|
| Go | `bin/world` | `GET /go-world/{id}`, `POST /go-world` |
| Node.js | `js/handler.hello` | `POST /js-world` |
| Python | `py.handler.hello` | `DELETE /py-world/{id}` |

## Structure

```
├── go/              # Go Lambda handlers
│   ├── lib/         # Shared AWS utilities
│   └── world/       # World handler
├── js/              # Node.js handlers
├── py/              # Python handlers
├── json_schema/     # Request validation schemas
└── serverless.yml   # Serverless Framework config
```

## Features

- Multi-language Lambda deployment
- API Gateway integration with API keys
- Request schema validation
- LocalStack support for local development

## Local Development

```bash
# Start LocalStack
docker-compose up -d

# Deploy to LocalStack
sls deploy --stage local

# Test endpoint
curl localhost:4566/restapis/<rest-api-id>/local/_user_request/go-world
```

## Build & Deploy

```bash
make build
sls deploy
```
