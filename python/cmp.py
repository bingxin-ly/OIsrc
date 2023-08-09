from cyaron import *


def rand():
    return (randint(1, n), randint(1, n))


for i in range(10):
    data = IO(".in")
    n = 5
    m = 10
    data.input_writeln(n, m)
    for _ in range(m):
        u = v = 1
        while u == v:
            u, v = rand()
        data.input_writeln(u, v, randint(1, 5), randint(1, 10))
    Compare.program(
        R"C:\OIsrc\output\6880flip_SPT.exe",
        input=data,
        std_program=R"C:\OIsrc\output\temp.exe",
    )
    # data.output_gen(R'D:\OIsrc\output\temp.exe')
    print(f"{i + 1} test, no problem")
