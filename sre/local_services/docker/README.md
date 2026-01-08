# Docker Compose Setup

This directory contains the Docker Compose configuration for running the local services stack.

## Prerequisites

1.  **Docker Desktop** (or equivalent Docker engine) installed.
2.  **Google Cloud Credentials**: Ensure you have `application_default_credentials.json` in the `creds/` directory at the project root.

## Quick Start

### 1. Build the Shared Image
Since we share the `golinks` image between Docker Compose and Kubernetes, you need to build it locally first.

Run this from the **project root**:
```bash
docker build -t golinks:local ./golinks
```

### 2. Start Services
Start the stack using Docker Compose:

```bash
docker compose -f docker/docker-compose.yml up -d
```

### 3. Verify
Check if containers are running:
```bash
docker ps
```

You should see:
- `traefik` (Reverse Proxy)
- `golinks` (The Go application)
- `postgres`
- `mysql`
- `redis`

## Accessing Services

- **Golinks**: `http://go` (Requires `/etc/hosts` entry: `127.0.0.1 go`)
- **Traefik Dashboard**: `http://localhost:8080` (if enabled in config)
- **Databases**: Exposed on their standard ports (`3306`, `5432`, `6379`) on localhost.
