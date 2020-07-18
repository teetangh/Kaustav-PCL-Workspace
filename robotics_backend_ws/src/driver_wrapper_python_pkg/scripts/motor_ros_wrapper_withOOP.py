#!/usr/bin/env python

import rospy
# from motor_driver import MotorDriver
from ..src.my_robot_driver import MotorDriver

from std_msgs import Int32
from std_srvs import Trigger

from diagnostic_msgs.msg import DiagnosticStatus
from diagnostic_msgs.msg import KeyValue

class MotorDriverROSWrapper:

    def __init__(self):
        # self.motor = MotorDriver(max_speed=8)

        max_speed = rospy.get_param("~max_speed", 8)
        self.motor = MotorDriver(max_speed=max_speed)

        rospy.Subsriber("speed_command", Int32, self.callback_speed_command)

        rospy.Service("stop_motor", Trigger, self.callback_stop)
        
        publish_current_speed_frequency = rospy.get_param("~publish_current_speed_frequency" , 5.0)
        publish_motor_status_frequency = rospy.get_param("~publish_motor_status_frequency", 1.0)

        self.current_speed_pub = rospy.Publisher("current_speed" , Int32 , queue_size = 10)
        self.motor_status_pub = rospy.Publisher("motor_status" , DiagnosticStatus , queue_size = 1)

        rospy.Timer(rospy.Duration(1.0/publish_current_speed_frequency) , self.publish_current_speed)
        rospy.Timer(rospy.Duration(1.0/publish_motor_status_frequency) , self.publish_motor_status)

    def publish_current_speed(self, event= None):
        self.current_speed_pub.publish(self.motor.get_speed())

    def publish_motor_status (self , event = None):
        status = self.motor.get_status()
        data_list = []

        for key in status:
            data_list.append(KeyValue(key , str(status[key])))

            msg = DiagnosticStatus()
            msg.values = data_list

            self.motor_status_pub.publish(msg)

    def stop(self):
        self.motor.stop()
    
    def callback_speed_command(self, msg):
        self.motor.set_speed(msg.data)


    def callback_stop(self, req):
        self.stop()
        return {"success": True, "message": "Motor has been stopped"}

if __name__ == "__main__":
    rospy.init_node("motor_driver")

    motor_driver_wrapper = MotorDriverROSWrapper()
    rospy.on_shutdown(motor_driver_wrapper.stop())

    rospy.loginfo("Motor driver is now started,ready to get commands")
    rospy.spin()
