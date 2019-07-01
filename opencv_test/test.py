import cv2
from matplotlib import pyplot as plt

def handle_key_press(event):
	if event.key == 'x':
		plt.close()	
fig = plt.figure()
fig.canvas.mpl_connect('key_press_event', handle_key_press)
imageFile = 'lena.jpg'
# Grayscale 포맷으로 읽어서 imgGray 객체에 저장한다.
imgGray = cv2.imread(imageFile, cv2.IMREAD_GRAYSCALE)
# plt.figure 크기를 (6,6) 인치로 설정
plt.imshow(imgGray, cmap = 'gray')
#plt.axis('tight')
plt.axis('off')
plt.show()
