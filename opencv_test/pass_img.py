import cv2
import matplotlib.pyplot as plt
num = 0
ext = '.jpg'
img = 'lena2'
def onclick(event):
	global num
	global img
	num +=1
	if num == 1:
		img = 'monkey2'
	elif num == 2:
		img = 'apple2'
	elif num == 3:
		img = 'orange2'
	else:
		plt.close()
		return
	img1 = cv2.imread(img + ext)
	img2 = cv2.cvtColor(img1, cv2.COLOR_BGR2RGB)		
	print(num)

def onclick2(event):
	print("onclick")

def draw_pic():
	fig = plt.figure(figsize=(10,6))
	plt.axis('off')

	fig.canvas.set_window_title('IMAGE PASS')
	cid = fig.canvas.mpl_connect('button_press_event', onclick)
	img1 = cv2.imread(img + ext)
	img2 = cv2.cvtColor(img1, cv2.COLOR_BGR2RGB)
	plt.imshow(img2)
	plt.show()
while True:
	draw_pic()
	if num == 4:
		break
