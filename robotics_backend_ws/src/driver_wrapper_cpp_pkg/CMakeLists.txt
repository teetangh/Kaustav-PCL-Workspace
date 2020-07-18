cmake_minimum_required(VERSION 3.0.2)
project(driver_wrapper_cpp_pkg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node_withOOP src/motor_ros_wrapper_withOOP.cpp)
target_link_libraries(${PROJECT_NAME}_node_withOOP ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_node_withoutOOP src/motor_ros_wrapper_withoutOOP.cpp)
target_link_libraries(${PROJECT_NAME}_node_withoutOOP ${catkin_LIBRARIES})
