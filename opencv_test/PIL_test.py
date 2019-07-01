from PIL import Image

path = './'
ext = '.jpg'
img = input("사진 입력: ")
im = Image.open(path+img+ext)

img1 = im.resize((600, 600))
img1.save(path+img+'2'+ext)
