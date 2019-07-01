import cv2

img = '/home/jiwoong/opencv_python_test/index.jpeg'

img1 = cv2.imread(img)

cv2.imshow('Lena', img1)

cv2.waitKey()
cv2.destroyAllWindows()
