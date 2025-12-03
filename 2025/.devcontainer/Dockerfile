FROM mcr.microsoft.com/devcontainers/go:1-1.23-bookworm

# when not setting correct permissions
# we have to delete the cache by ourselves
# everytime we start a new session of the devcontainer
ENV GOMODCACHE=/workspaces/backend/.gocache 
RUN mkdir -p /workspaces/backend/.gocache && chown -R vscode:vscode /workspaces/backend/.gocache

# this version works; others fail due to persmission issues - I the fuck don'T know why...
RUN go install golang.org/x/tools/gopls@v0.16.1

# Install go migration tool
# here in dockerfile for efficient caching
RUN curl -L https://github.com/golang-migrate/migrate/releases/download/v4.16.2/migrate.linux-amd64.tar.gz \
    | tar xz && \
    mv migrate /usr/local/bin/ && \
    chmod +x /usr/local/bin/migrate

# Swagger support in Go (Code Generation based on comments)
RUN go install github.com/swaggo/swag/cmd/swag@latest

# Install AWS CLI
RUN apt-get update && apt-get install -y \
    unzip \
    curl && \
    curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip" && \
    unzip awscliv2.zip && \
    ./aws/install && \
    rm -rf awscliv2.zip aws