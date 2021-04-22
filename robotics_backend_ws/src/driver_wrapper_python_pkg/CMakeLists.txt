cmake_minimum_required(VERSION 3.0.2)
project(driver_wrapper_python_pkg)

find_package(catkin REQUIRED COMPONENTS
  rospy
)

catkin_python_setup()

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)
