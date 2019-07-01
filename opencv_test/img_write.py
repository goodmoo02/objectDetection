import cv2
img = '/home/jiwoong/objectDetection/opencv_test/index.jpeg'

img1 = cv2.imread(img)

cv2.imwrite('/home/jiwoong/objectDetection/opencv_test/lena.png', img1)
cv2.imwrite('/home/jiwoong/objectDetection/opencv_test/lena.bmp', img1)


