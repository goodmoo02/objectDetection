# 영상 출력
import cv2
capture = cv2.VideoCapture("./Yeonwoo.mp4")
print(capture.get(cv2.CAP_PROP_FPS))
while True:
    if(capture.get(cv2.CAP_PROP_POS_FRAMES) == capture.get(cv2.CAP_PROP_FRAME_COUNT)):
                  # 현재 프레임 개수                      # 총 프레임 개수
        capture.open("./Yeonwoo.mp4")

    ret, frame = capture.read()
    cv2.imshow("VideoFrame", frame)
    if cv2.waitKey(5) > 0: break # 5ms마다 key 확인.  0으로 설정하면, 프레임이 변경되지 않는다.
# capture.release()
cv2.destroyAllWindows()
