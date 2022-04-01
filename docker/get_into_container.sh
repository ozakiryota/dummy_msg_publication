#!/bin/bash

xhost +

image="dummy_msg_publication"
tag="latest"

docker run -it --rm \
	-e "DISPLAY" \
	-v "/tmp/.X11-unix:/tmp/.X11-unix:rw" \
	-v $(pwd)/..:/root/catkin_ws/src/$image \
	$image:$tag