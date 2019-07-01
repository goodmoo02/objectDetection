from PIL import Image

im = Image.open('lena.jpg')
im.show()
crp = im.crop((100, 100, 350, 350))
crp.show()
crp.save('lena-crop.jpg')

