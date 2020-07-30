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
        # drawImg = orig

        # Resized Image
        # Resize the Single-Channel Image
        resized = cv2.resize(src=orig, dsize=None, fx=0.5, fy=0.5)
        drawImg = resized

        # Convert to Single Channel
        gray = cv2.cvtColor(src=resized, code=cv2.COLOR_BGR2GRAY)
        drawImg = cv2.cvtColor(src=gray, code=cv2.COLOR_GRAY2BGR)

        # Applying a thresholding to the image
        threshVal = 150
        ret, thresh = cv2.threshold(
            src=gray, thresh=threshVal, maxval=255, type=cv2.THRESH_BINARY)
        drawImg = cv2.cvtColor(src=thresh, code=cv2.COLOR_GRAY2BGR)

        # detect the outer pump circle
        pumpRadiusRange = (PUMP_DIAMETER/2 - 2, PUMP_DIAMETER/2 + 2)
        pumpCircles = cv2.HoughCircles(image=thresh, method=cv2.HOUGH_GRADIENT, dp=1, minDist=PUMP_DIAMETER,
                                       param2=2, minRadius=pumpRadiusRange[0], maxRadius=pumpRadiusRange[1])

        # Plotting the circles with Error Checking
        plotCircles(img=drawImg, circles=pumpCircles, color=(255, 0, 0))
        if (pumpCircles is None):
            raise Exception("No pump circles found")
        elif len(pumpCircles[0]) != 1:
            raise Exception("Wrong # of pump circles found: {} expected {} ".format(
                len(pumpCircles[0]), 1))
        else:
            pumpCircle = pumpCircles[0][0]

        # detect the blobs inside the pump body
        pistonArea = 3.14159 * PISTON_DIAMETER ** 2 / 4
        blobParams = cv2.SimpleBlobDetector_Params()
        blobParams.filterByArea = True
        blobParams.minArea = 0.8 * pistonArea
        blobParams.maxArea = 1.2 * pistonArea
        blobDetector = cv2.SimpleBlobDetector_create(blobParams)
        blobs = blobDetector.detect(thresh)

        # OpenCV check
        drawImg = cv2.drawKeypoints(image=drawImg, keypoints=blobs, outImage=(), color=(
            0, 255, 0), flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

        if len(blobs) != PISTON_COUNT:
            raise Exception("Wrong # of pistons: found {} expected {}".format(
                len(blobs), PISTON_COUNT))
        # pistonCenters = [(int(b.pt[0], int(b.pt[1]))) for b in blobs]

        # Finally showing the size
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
