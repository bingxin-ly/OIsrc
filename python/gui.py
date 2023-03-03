import tkinter as tk
from queue import Queue
from PIL import Image, ImageTk
from pic import get_image

img_open = None
img_sized = None
img_transed = None
cached_pics = Queue()

pull_image = lambda: [cached_pics.put(x) for x in get_image(1)]
update_pos = lambda width, height: window.geometry(
    '%dx%d+%d+%d' % (width, height, (window.winfo_screenwidth() - width) / 2,
                     (window.winfo_screenheight() - height) / 2))


def f(n):
    std_size = 300
    if n < std_size:
        return n
    return int((n / std_size)**0.3 * std_size)


def adjust(img, size):
    width, height = img.size
    if height > width:  # 高 是 长边
        height_ = size  # 直接将高调整为目标尺寸
        scale = height_ / height  # 计算高具体调整了多少，得出一个放缩比例
        width_ = int(width * scale)  # 宽以相同的比例放缩
    else:  # 同上
        width_ = size
        scale = width_ / width
        height_ = int(height * scale)

    img = img.resize((width_, height_), Image.HAMMING)  # 将高和宽放缩
    return img


def refresh():
    global img_open, img_sized, img_transed

    if cached_pics.empty():
        pull_image()

    img_open = Image.open("./pics/%s" % cached_pics.get_nowait())
    imgx, imgy = img_open.size
    img_sized = adjust(img_open, f(max(imgx, imgy)))

    width, height = img_sized.size
    window.geometry('%dx%d' % (width + 20, height + 200))

    img_transed = ImageTk.PhotoImage(img_sized)
    label_img = tk.Label(window, image=img_transed)
    label_img.grid(row=1)


if __name__ == '__main__':
    window = tk.Tk()
    update_pos(500, 700)

    pull_image()
    button = tk.Button(window, text="  刷新  ", command=refresh, bd=1)
    button.grid(row=0)
    refresh()

    window.mainloop()
