import cv2
cap = cv2.VideoCapture('http://192.168.1.21:4747/video') # droid cam

while True:
	retval, frame = cap.read() # 프레임 캡처
	if not retval:
		break
	height, width, channel = frame.shape
	matrix = cv2.getRotationMatrix2D((width/2, height/2), -90, 1)
	frame = cv2.warpAffine(frame, matrix, (width, height))
	cv2.imshow('frame',frame)

	key = cv2.waitKey(25)
	if key == 27: # Esc
		break
if cap.isOpened():
	cap.release()
cv2.destroyAllWindows()
