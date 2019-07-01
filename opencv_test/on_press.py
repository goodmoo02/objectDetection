import cv2
from matplotlib import pyplot as plt

def on_press(event):
	print('you pressed', event.button, int(event.xdata), int(event.ydata))

fig = plt.figure(figsize=(10, 6)) # fig.set_size_inches(10, 6)


fig.canvas.set_window_title('Video Capture')
cid = fig.canvas.mpl_connect('button_press_event', on_press)

img = 'lena.jpg'
img1 = cv2.imread(img, cv2.IMREAD_GRAYSCALE)
plt.axis('off')

plt.imshow(img1, cmap = "gray", interpolation='bicubic')
plt.show()
