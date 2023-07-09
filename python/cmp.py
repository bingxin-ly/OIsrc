from cyaron import *

for i in range(10):
    data = IO(".in")
    n = 4
    m = 6
    data.input_writeln(0, n)
    for _ in range(m):
        op = randint(1, 2)
        if op == 1:
            data.input_writeln(1, randint(1, n), randint(1, n), randint(1, 2))
        else:
            x1, y1 = randint(1, n - 1), randint(1, n - 1)
            x2, y2 = randint(x1, n), randint(y1, n)
            data.input_writeln(2, x1, y1, x2, y2)
    data.input_writeln(3)
    Compare.program(
        R"C:\OIsrc\output\4390mokia.exe",
        input=data,
        std_program=R"C:\OIsrc\output\temp.exe",
    )
    # data.output_gen(R'D:\OIsrc\output\temp.exe')
    print(f"{i + 1} test, no problem")
