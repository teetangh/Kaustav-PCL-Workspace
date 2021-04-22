cmake_minimum_required(VERSION 3.0.2)
project(detect_pump)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  rospy
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)
