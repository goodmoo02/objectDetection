import cv2

src = cv2.imread("lena.jpg", cv2.IMREAD_COLOR)
b,g,r = cv2.split(src)
inversebgr = cv2.merge((g,g,g))

cv2.imshow("inverse", inversebgr)
cv2.waitKey(0)
cv2.destroyAllWindows()
