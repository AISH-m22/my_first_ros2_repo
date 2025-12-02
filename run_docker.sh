#!/bin/bash

# Name of Docker image and container
IMAGE_NAME="my_circle_pkg"
CONTAINER_NAME="my_circle_container"

# Build Docker image
echo "Building Docker image..."
docker build -t $IMAGE_NAME .

# Remove old container if it exists
echo "Removing any existing container..."
docker rm -f $CONTAINER_NAME 2>/dev/null || true

# Run container with GUI support
echo "Starting container..."
docker run -it --name $CONTAINER_NAME \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    $IMAGE_NAME
