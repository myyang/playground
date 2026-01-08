# Local Services

This repository manages the local development environment for SRE services, supporting both **Docker Compose** and **Kubernetes (k3d)** workflows.

## Architecture

The project is structured to share resources where possible (like the `golinks` image) while allowing flexibility in orchestration.

```
.
├── dockerfiles/      # Service dockerfiles
├── docker/           # Docker Compose configuration and documentation
├── k8s/              # Kubernetes manifests and documentation
└── creds/            # Google Cloud credentials (ignored by git)
```

## Shared Setup (Required)

Before running either Docker Compose or Kubernetes, you must build the local image.

### 1. Google Cloud Credentials
Authenticate and generate the default credentials file:
```bash
gcloud auth application-default login
# Ensure the file is saved to ./creds/application_default_credentials.json
```

### 2. Build Image
Build the `golinks` image locally so it can be used by both environments:
```bash
docker build -t golinks:local ./dockerfiles/golinks
```

### 3. DNS Setup
Map the `go` hostname to localhost for easy access:
```bash
sudo echo "127.0.0.1 go" >> /etc/hosts
```

## Running the Stack

You can choose to run the stack using Docker Compose or Kubernetes.

### Option A: Docker Compose
Simple and fast for pure local development.
-> See [docker/README.md](docker/README.md) for details.

```bash
docker compose -f docker/docker-compose.yml up -d
```

### Option B: Kubernetes (k3d)
Closer to production environment.
-> See [k8s/README.md](k8s/README.md) for details.

Summary:
1. Create/Start k3d cluster.
2. Import the image: `k3d image import golinks:local -c <cluster-name>`
3. Apply manifests: `kubectl apply -f k8s/`
