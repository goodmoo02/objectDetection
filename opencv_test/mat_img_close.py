import cv2
import matplotlib.pyplot as plt
# 키 입력을 위한 함수
def handle_key_press(event):
	if event.key == 'escape':
		cap.release()
		plt.close()


# 종료 이벤트를 처리하기 위한 함수
def handle_close(evt):
	print('Close figure!')
	cap.release()
# 프로그램 시작
cap = cv2.VideoCapture('./Yeonwoo.mp4') # 0번 카메라

# interactive on
plt.ion() # 대화모드 설정
fig = plt.figure(figsize=(10, 6)) # fig.set_size_inches(10, 6)
plt.axis('off')

#ax = fig.gca()
#ax.set_axis_off()

fig.canvas.set_window_title('Video Capture')
fig.canvas.mpl_connect('key_press_event', handle_key_press)
fig.canvas.mpl_connect('close_event', handle_close)
retval, frame = cap.read() # 첫 프레임 캡처
im = plt.imshow(cv2.cvtColor(frame, cv2.COLOR_BGR2RGB))
#3
while True:
	retval, frame = cap.read() # 프레임 캡처
	if not retval:
		break
# plt.imshow(cv2.cvtColor(frame, cv2.COLOR_BGR2RGB))
	im.set_array(cv2.cvtColor(frame, cv2.COLOR_BGR2RGB))
	fig.canvas.draw() # canvas update
# fig.canvas.draw_idle()
	fig.canvas.flush_events() # plt.pause(0.001)
if cap.isOpened():
	cap.release()

# fig, ax = plt.subplots()
# ax.plot(np.random.rand(10)

#def onclick(event):
#	print('%s click: button=%d, x=%d, y=%d, xdata=%f, ydata=%f' %('double' if event.dblclick else 'single', event.button, event.x, event.y, event.xdata, event.ydata))


#cid = fig.canvas.mpl_connect('button_press_event', onclick)

