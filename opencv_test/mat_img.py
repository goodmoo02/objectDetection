import cv2

from matplotlib import pyplot as plt

img = './index.jpeg'

img1 = cv2.imread(img)

plt.axis('off')

imgRGB = cv2.cvtColor(img1,cv2.COLOR_BGR2RGB)
plt.imshow(imgRGB)
plt.show()
