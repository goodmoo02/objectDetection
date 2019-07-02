import numpy as np
import cv2
def onChange(pos): # 트랙바 핸들러
	global img
	h = cv2.getTrackbarPos('H','img')
	s = cv2.getTrackbarPos('S','img')
	v = cv2.getTrackbarPos('V','img')
	img[:] = (h, s, v)
	cv2.imshow('img', img)
	img = np.zeros((512, 512, 3), np.uint8)
	cv2.imshow('img',img)
# 트랙바 생성
cv2.createTrackbar('H', 'img', 0, 180, onChange)
cv2.createTrackbar('S', 'img', 0, 255, onChange)
cv2.createTrackbar('V', 'img', 0, 255, onChange)
# 트랙바 위치 초기화
cv2.setTrackbarPos('H', 'img', 0)
cv2.setTrackbarPos('S', 'img', 0)
cv2.setTrackbarPos('V', 'img', 255)
cv2.waitKey()
cv2.destroyAllWindows() 
