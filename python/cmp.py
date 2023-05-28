from cyaron import *
from math import gcd
from random import randint
for i in range(100):
    n = randint(1, 1 << 31 - 2)
    m = randint(n, 1 << 31 - 1)
    data = IO('test.in', 'test.out')
    data.input_writeln(n, m)
    data.output_gen('D:\\src\\output\\temp.exe')
    with open('./std.out', 'w') as f:
        f.write(str(gcd(n, m)))
    Compare.output('./std.out', std='./test.out')
    print(f'{i + 1} no problem')