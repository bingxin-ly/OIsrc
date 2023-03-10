P = 19260817
x, y = 0, 0


def exgcd(a: int,  b: int):
    global x, y
    if b == 0:
        x = 1
        y = 0
    else:
        exgcd(b, a % b)
        tmp = x
        x = y
        y = tmp - a // b * y


a, b = int(input()), int(input())
a %= P
b %= P
if b == 0:
    print("Angry!")
else:
    exgcd(b, P)
    print(a * x % P)
