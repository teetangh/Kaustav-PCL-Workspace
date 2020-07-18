#include <ros/ros.h>
#include "../include/motor_driver.hpp"

int main(int argc, char const *argv[])
{
    ros::init(argc, argv, "motor_driver");
    ros::NodeHandle nh;

    ros::AsyncSpinner spinner(4);
    spinner.start();

    MotorDriver motor = MotorDriver(8);
    ROS_INFO("Motor is now started");

    // ros::spin();
    ros::
    motor.stop();

    return 0;
}
