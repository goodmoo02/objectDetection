import cv2
from matplotlib import pyplot as plt

num = 0
ext = '.jpg'
img = 'lena2'

img = cv2.imread(img + ext)
fig = plt.figure(figsize=10,6))
plt.axis('off')
fig.canvas.set_window_title('IMAGE')


