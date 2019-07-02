import cv2
import numpy as np
# White 배경 생성
img = np.zeros(shape=(512,512,3), dtype=np.uint8) + 255
#img = np.ones((512,512,3), np.uint8) * 255
#img = np.full((512,512,3), (255, 255, 255), dtype= np.uint8)
#img = np.zeros((512,512, 3), np.uint8) # Black 배경
x1, y1 = 100, 100
x2, y2 = 400, 400
#color(B,G,R)
pt1 = 10, 50
pt2 = 500, 350
cv2.rectangle(img, (x1,y1), (x2,y2), (0, 255, 0), 2)
#cv2.rectangle(img, pt1, pt2, (255, 0 ,0), -1)
cv2.line(img, pt1, pt2, (255, 0, 0), 5)
imgRect = (x1, y1, x2-x1, y2-y1)
retval, rpt1, rpt2 = cv2.clipLine(imgRect, pt1, pt2)
if retval:
	cv2.circle(img, rpt1, radius=5, color=(0,255,0), thickness=-1)
	cv2.circle(img, rpt2, radius=5, color=(0,255,0), thickness=-1)
cv2.imshow('img', img)
cv2.waitKey()
cv2.destroyAllWindows()
