import matplotlib.pyplot as plt
import numpy as np
fig, ax = plt.subplots()
ax.plot(np.random.rand(10)

def onclick(event):
	print("onclick")
fig.canvas.mpl_connect('button_press_event', onclick)

# fig.canvas.mpl_disconnect(cid)

