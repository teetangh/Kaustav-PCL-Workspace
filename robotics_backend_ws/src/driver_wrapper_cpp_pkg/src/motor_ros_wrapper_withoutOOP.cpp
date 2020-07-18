#include <ros/ros.h>
#include "../include/my_robot_driver/motor_driver.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "driver_wrapper_cpp_pkg_withoutOOP");
    ros::NodeHandle nh;

    ros::AsyncSpinner spinner(4);
    spinner.start();

    MotorDriver motor = MotorDriver(8);
    ROS_INFO("Motor is now started");

    // ros::spin();
    ros::motor.stop();

    return 0;
}
