#!/usr/bin/env python
import rospy
import sys
from cv2 import cv2
from cv_bridge import CvBridge
from sensor_msgs.msg import Image


def start_node(filename):
    rospy.init_node('image_pub')
    rospy.loginfo('image_pub node has started')
    img = cv2.imread(filename=filename)

    # cv2.imshow("image", img)
    # cv2.waitKey(2000)

    bridge = CvBridge()
    imgMsg = bridge.cv2_to_imgmsg(cvim=img, encoding="bgr8")

    pub = rospy.Publisher(name='image', data_class=Image, queue_size=10)
    # pub = rospy.Publisher('image', Image, queue_size=10)

    while not rospy.is_shutdown():
        pub.publish(imgMsg)
        rospy.Rate(1.0).sleep()  # 1 Hz


if __name__ == "__main__":
    try:
        start_node(rospy.myargv(argv=sys.argv)[1])
    except rospy.ROSInterruptException:
        pass
