#!/bin/bash

image="dummy_msg_publication"
tag="latest"

docker build . \
    -t $image:$tag \
    --build-arg CACHEBUST=$(date +%s)