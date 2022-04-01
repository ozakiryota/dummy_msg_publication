########## Pull ##########
FROM ros:noetic
########## Non-interactive ##########
ENV DEBIAN_FRONTEND=noninteractive
########## Common tool ##########
RUN apt-get update && \
	apt-get install -y \
		vim \
		wget \
		unzip \
		git \
        python-tk
########## ROS setup ##########
RUN mkdir -p ~/catkin_ws/src && \
	cd ~/catkin_ws && \
	/bin/bash -c "source /opt/ros/noetic/setup.bash; catkin_make" && \
	echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc && \
	echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc && \
	echo "export ROS_WORKSPACE=~/catkin_ws" >> ~/.bashrc
## cmk
RUN echo 'function cmk(){ \n\
		lastpwd=$OLDPWD \n\
		cpath=$(pwd) \n\
		cd ~/catkin_ws \n\
		catkin_make $@ \n\
		cd $cpath \n\
		OLDPWD=$lastpwd \n\
        }' >> ~/.bashrc
########## dummy_msg_publication ##########
## dependencies
RUN apt-get update && \
    apt-get install -y \
		libpcl-dev \
		ros-noetic-pcl-conversions \
		ros-noetic-rviz
## cache busting
ARG CACHEBUST=1
## build
RUN cd ~/catkin_ws/src && \
	git clone https://github.com/ozakiryota/dummy_msg_publication.git && \
	cd ~/catkin_ws/ && \
	/bin/bash -c "source /opt/ros/noetic/setup.bash; catkin_make"
########## Initial position ##########
WORKDIR /root/catkin_ws/src/dummy_msg_publication