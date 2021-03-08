#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
from cv2 import cv2

# known pump geometry
# - units are pixels (of half size)
PUMP_DIAMETER = 360
PISTON_DIAMETER = 90
PISTON_COUNT = 7


def start_node():
    rospy.init_node('detect_pump')
    rospy.loginfo('detec_pump node has started')

    rospy.Subscriber(name="image", data_class=Image, callback=process_image)
    rospy.spin()


def plotCircles(img, circles, color):
    if circles is None:
        return

    for (x, y, r) in circles[0]:
        cv2.circle(img=img, center=(int(x), int(y)),
                   radius=int(r), color=color, thickness=2)


def process_image(msg):
    try:
        # convert sensor_msgs/Image to OpenCV Image
        bridge = CvBridge()

        # original Image
        orig = bridge.imgmsg_to_cv2(msg, "bgr8")
        drawImg = orig
        ShowImage(drawImg)
    except Exception as err:
        print(err)


def ShowImage(img):
    cv2.imshow("ROS to CV2 Image", img)
    cv2.waitKey(1)


if __name__ == "__main__":
    try:
        start_node()

    except rospy.ROSInterruptException:
        pass
