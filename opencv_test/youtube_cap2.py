import cv2
capture = cv2.VideoCapture("./Yeonwoo.mp4")
print(capture.get(cv2.CAP_PROP_FPS))
while True:
    if(capture.get(cv2.CAP_PROP_POS_FRAMES) == capture.get(cv2.CAP_PROP_FRAME_COUNT)):
                  # 현재 프레임 개수                      # 총 프레임 개수
        capture.open("./Yeonwoo.mp4")

    ret, frame = capture.read()
    canny = cv2.Canny(frame, 100, 255)
    cv2.imshow("VideoFrame", canny)

    if cv2.waitKey(30) > 0: break # 5ms마다 key 확인.  0으로 설정하면, 프레임이 변경되지 않는다.

capture.release()
cv2.destroyAllWindows()
