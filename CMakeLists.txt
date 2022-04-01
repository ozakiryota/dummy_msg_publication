cmake_minimum_required(VERSION 3.0.2)
project(dummy_msg_publication)

add_compile_options(-std=c++14 -O2 -g -Wall)

find_package(catkin REQUIRED
    roscpp
)
find_package(PCL)

################################################
## Declare ROS messages, services and actions ##
################################################

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

catkin_package(
)

###########
## Build ##
###########

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${PCL_INCLUDE_DIRS}
)

add_executable(pointcloud2 src/pointcloud2.cpp)
target_link_libraries(pointcloud2
    ${catkin_LIBRARIES}
    ${PCL_LIBRARIES}
)

#############
## Install ##
#############

#############
## Testing ##
#############
