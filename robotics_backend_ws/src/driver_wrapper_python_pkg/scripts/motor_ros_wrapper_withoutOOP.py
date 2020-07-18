#!/usr/bin/env python

import rospy
from driver_wrapper_python_pkg.src.my_robot_driver.motor_driver import MotorDriver


if __name__ == "__main__":
    rospy.init_node("motor_driver")

    motor = MotorDriver(max_speed = 8)
    rospy.on_shutdown(motor.stop)

    rospy.loginfo("Motor driver is now started,ready to get commands")
    rospy.spin()

