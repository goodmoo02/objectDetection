import cv2

from matplotlib import pyplot as plt

img = './index.jpeg'

img1 = cv2.imread(img, cv2.IMREAD_GRAYSCALE)

plt.axis('off')

plt.imshow(img1, cmap="gray", interpolation='bicubic')
plt.show()
