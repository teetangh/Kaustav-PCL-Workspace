cmake_minimum_required(VERSION 3.0.2)
project(opencv_tutorial_python)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  opencv
  rospy
  sensor_msgs
  std_msgs
)
catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)
