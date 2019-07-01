import cv2, pafy
url = "https://www.youtube.com/watch?v=eRN4WmoaCDY"
video = pafy.new(url)

best = video.getbest(preftype='webm') # ‘mp4’,'3gp' 의 최적의 해상도를 찾아준다.
cap=cv2.VideoCapture(best.url)

while True:
    if(cap.get(cv2.CAP_PROP_POS_FRAMES) == cap.get(cv2.CAP_PROP_FRAME_COUNT)):
                  # 현재 프레임 개수                      # 총 프레임 개수
        cap.open(best.url)

    ret, frame = cap.read()
    canny = cv2.Canny(frame, 100, 255)
    cv2.imshow("VideoFrame", canny)

    if cv2.waitKey(30) > 0: break # 5ms마다 key 확인.  0으로 설정하면, 프레임이 변경되지 않는다.

cap.release()
cv2.destroyAllWindows()
