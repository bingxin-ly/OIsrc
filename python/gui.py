import tkinter as tk
from PIL import Image, ImageTk
from pic import get_image

std_size = 200
img_name = ''
img_open = None
img_sized = None
img_transed = None


def update_pos(width, height):
    window.geometry('%dx%d+%d+%d' %
                    (width, height + 60, (window.winfo_screenwidth() - width - 20),
                     (window.winfo_screenheight() - height - 150)))


def f(n):
    global std_size
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
    global img_name, img_open, img_sized, img_transed

    img = get_image(1)
    img_name = img[0][0]
    img_open = Image.open(img[0][1])
    imgx, imgy = img_open.size
    img_sized = adjust(img_open, f(max(imgx, imgy)))

    width, height = img_sized.size
    # window.geometry('%dx%d' % (width, height))
    update_pos(width, height)

    img_transed = ImageTk.PhotoImage(img_sized)
    label_img = tk.Label(window, image=img_transed)
    label_img.grid(row=2, sticky='nw')


if __name__ == '__main__':
    window = tk.Tk()

    tk.Button(window, text='  刷新  ', command=refresh, bd=1).grid(row=0)
    tk.Button(window, text='  保存  ', command=lambda:
              img_open.save('./pics/%s' % img_name), bd=1).grid(row=1)
    refresh()

    window.mainloop()
