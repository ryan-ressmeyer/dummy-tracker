#!/bin/bash

DOCKER_OPTIONS="--rm -ti --ipc=host -p 127.0.0.1:5555:5555/tcp"

docker run $DOCKER_OPTIONS dummy:latest ./dummy "$@"
   