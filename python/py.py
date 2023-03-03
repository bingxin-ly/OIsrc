import tkinter as tk
from PIL import Image, ImageTk
import cv2
import os


def btnHelloClicked():
    labelHello.config(text="Hello Tkinter!")


def resize(w, h, w_box, h_box, im):
    f1 = 1.0 * w_box / w
    f2 = 1.0 * h_box / h
    factor = min([f1, f2])
    width = int(w * factor)
    height = int(h * factor)
    return im.resize((width, height), Image.ANTIALIAS)


top = tk.Tk()
#-------------- image 1 --------------
# for N in range(1, 10):
if True:
    filename = 'C:\\Users\\Chris\\Pictures\\th.jfif'
    if os.path.isfile(filename):
        # top = tk.Toplevel()#tk.Tk()
        top.title("test the net.")
        # string
        labelHello = tk.Label(top, text='th', height=5, width=20, fg="blue")
        labelHello.grid(row=0, column=1)
        img1 = cv2.imread(filename)
        im1 = Image.fromarray(cv2.cvtColor(img1, cv2.COLOR_BGR2RGB))
        # ---resize the image to w_box*h_box
        w_box = 500
        h_box = 450
        w, h = im1.size
        im_resized1 = resize(w, h, w_box, h_box, im1)

        bm1 = ImageTk.PhotoImage(image=im_resized1)
        label1 = tk.Label(top, image=bm1, width=w_box, height=h_box)
        label1.grid(row=1, column=0)
        top.update()
        top.after(1000)
top.mainloop()
