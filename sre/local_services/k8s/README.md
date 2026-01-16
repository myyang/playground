# Kubernetes Setup Guide

This guide explains how to run the local services stack on Kubernetes (specifically tested with **k3d**).

## Prerequisites
1. Install [k3d](https://k3d.io/) (Recommended for local dev) or enable Kubernetes in Docker Desktop.
2. Ensure `kubectl` is installed and pointing to your cluster.
3. Ensure you have built the base image: `docker build -t golinks:local ./golinks` (Run from project root).

## 1. Create Secrets
We need to load the Google credentials into Kubernetes as a secret.

```bash
# Create the secret from your existing file
kubectl create secret generic golinks-creds \
  --from-file=application_default_credentials.json=./creds/application_default_credentials.json
```

## 2. Import Image (k3d specific)
Since `golinks` is a local build, we need to load the image into the k3d cluster so Kubernetes can find it without pulling from a remote registry.

```bash
# Create cluster if you haven't already
# k3d cluster create k3d-cluster -p "80:80@loadbalancer"

# Import image to k3d (replace 'k3d-cluster' with your actual cluster name)
k3d image import golinks:local -c k3d-cluster
```
*Note: If using Docker Desktop Kubernetes, the image is usually available automatically if built locally.*

## 3. Deploy
Apply the configurations:

```bash
kubectl apply -f k8s/databases.yaml
kubectl apply -f k8s/golinks.yaml
```

## 4. Accessing Services

### Golinks
Add the domain mapping to your `/etc/hosts` if not already present:
`127.0.0.1 go`

Access via: http://go

### Databases
Databases (MySQL, Postgres, Redis) are not exposed via Ingress by default (since they are TCP, not HTTP).
To access them locally, use `port-forward`:

```bash
# MySQL
kubectl port-forward svc/mysql 3306:3306

# Postgres
kubectl port-forward svc/postgres 5432:5432

# Redis
kubectl port-forward svc/redis 6379:6379

# ClickHouse
kubectl port-forward svc/clickhouse 8123:8123
```