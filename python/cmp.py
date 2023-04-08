from cyaron import *

for i in range(100):
    data = IO()
    # n = randint(1, int(2e5))
    # m = randint(1, int(2e5))
    # data.input_writeln(n, m, randint(1, n))
    for _ in range(randint(50, 100)):
        data.input_writeln(randint(1, 30))

    Compare.program('output\\temp.exe',
                    input=data,
                    std_program='output\\tst.exe')
    print('The %d times, no problem' % (i + 1))
