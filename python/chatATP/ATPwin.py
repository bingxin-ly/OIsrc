from tkinter import *
from tkinter.scrolledtext import *
from PIL import Image, ImageTk, ImageGrab

photos = []


class ATPWindow(Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.photo = None
        self.create_widgets()

    def create_widgets(self):
        self.text = ScrolledText(root, font=('黑体', 11), width=70, height=20)
        self.text.bind("<Key>", lambda _: "break")
        self.text.pack()

        self.entry = Text(root, width=65, height=5)
        self.entry.focus_set()
        self.entry.bind('<Key-Return>', self.input)
        self.entry.bind('<Control-v>', self.show)
        self.entry.pack(side=LEFT, padx=22)

        Button(root, text="发送", width=6, height=1,
               command=self.input).pack(side=RIGHT, padx=20)


    def show(self, _):
        image = ImageGrab.grabclipboard()
        if isinstance(image, Image.Image):
            x, y = image.size
            image = image.resize((50, 50 * y // x))
            self.photo = ImageTk.PhotoImage(image)
            self.entry.image_create(END, image=self.photo)

    def input(self, _=None):
        # 获取输入文本对象输入的内容
        msg = self.entry.get(1.0, END)
        self.print(msg)
        self.entry.delete('1.0', END)
        return 'break'

    def print(self, msg):
        global photos
        if self.photo != None:
            photos.append(self.photo)
            self.text.image_create(END, image=self.photo)
            self.photo = None
        self.text.insert(END, msg + '\n')
        self.text.see(END)
        return 'break'


if __name__ == '__main__':
    root = Tk()
    ww = 610
    wh = 400
    root.geometry("%dx%d+%d+%d" %
                  (ww, wh, (root.winfo_screenwidth() - ww) / 2,
                   (root.winfo_screenheight() - wh) / 2))

    app = ATPWindow(master=root)

    root.mainloop()
