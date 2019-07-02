import cv2
import numpy as np


def img_crop(img):
	max_x = 100
	max_y = 100
	x = np.random.randint(0, max_x)
	y = np.random.randint(0, max_y)

	crop = img[y:y + 350, x: x+350]

	return crop
def img_rotate(img):
	angle = 90
	scale = 1.
	H = img.shape[0]
	W = img.shape[1]
	matrix = cv2.getRotationMatrix2D((H/2,W/2), angle, scale)
	rotated = cv2.warpAffine(img, matrix, (H,W)) 
	return rotated

def mouse_callback(event, x, y, flags, param):
	global crop
	if event == cv2.EVENT_LBUTTONDBLCLK:
		img=img_crop(param)
		crop = img
		cv2.imshow("image", img)
	elif event == cv2.EVENT_MBUTTONDOWN: 
		crop = img_rotate(crop)
		cv2.imshow("image", crop)
		
img = cv2.imread('./lena.jpg')
img = cv2.resize(img, dsize = (521,521), interpolation=cv2.INTER_AREA)

crop = img_crop(img)
cv2.namedWindow('image')
cv2.setMouseCallback('image', mouse_callback,param = img)

cv2.imshow("image", crop)
while True:
	if cv2.waitKey(20) & 0xFF == 27:
		break
.destroyAllWindows()
nChange(pos): # 트랙바 핸들러
 global img
 r = cv2.getTrackbarPos('R','img')
 g = cv2.getTrackbarPos('G','img')
 b = cv2.getTrackbarPos('B','img')
 img[:] = (b, g, r)
 cv2.imshow('img', img)
img = np.zeros((512, 512, 3), np.uint8)
cv2.imshow('img',img)
# 트랙바 생성
cv2.createTrackbar('R', 'img', 0, 255, onChange)
cv2.createTrackbar('G', 'img', 0, 255, onChange)
cv2.createTrackbar('B', 'img', 0, 255, onChange)
# 트랙바 위치 초기화
#cv2.setTrackbarPos('R', 'img', 0)
#cv2.setTrackbarPos('G', 'img', 0)
cv2.setTrackbarPos('B', 'img', 255)
cv2.waitKey()
cv2.destroyAllWindows() 
