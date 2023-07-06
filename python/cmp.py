from cyaron import *

for i in range(100):
    data = IO("in")
    n = 1000
    m = 10
    data.input_writeln(n, m)
    for _ in range(n):
        data.input_write(randint(0, 1))
    data.input_writeln()
    for _ in range(m):
        l = randint(0, n - 2)
        r = randint(l + 1, n - 1)
        data.input_writeln(randint(0, 4), l, r)
    Compare.program(
        R"D:\OIsrc\output\2572seq_operation.exe",
        input=data,
        std_program=R"D:\OIsrc\output\temp.exe",
    )
    # data.output_gen(R"D:\OIsrc\output\temp.exe")
    print(f'{i + 1} test, no problem')
