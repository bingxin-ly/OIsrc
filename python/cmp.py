from cyaron import *

for i in range(100):
    data = IO("in", "out")
    n = randint(1, 30)
    data.input_writeln(n)
    for _ in range(n):
        data.input_writeln(randint(1, 1e3), randint(1, 1e3), randint(1, 1e3))
    data.input_writeln(0)
    Compare.program(
        R"D:\OIsrc\output\UVA437babylon.exe",
        input=data,
        std_program=R"D:\OIsrc\output\temp.exe",
    )
    print(f'{i + 1} test, no problem')
