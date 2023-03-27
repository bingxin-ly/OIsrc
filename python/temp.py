from cyaron import *

input_io = IO('output\hack')
input_io.input_writeln(Graph.hack_spfa(int(1e5), weight_limit=100))
exit(0)
for i in range(10):
    input_io = IO('hack')

    input_io.input_writeln(10, 20, 5, 1, 10)
    input_io.input_writeln(Graph(1e5, 2e6, hack_spfa=True))
    for j in range(5):
        input_io.input_writeln(j + 2)

    Compare.program('D:\\src\\3.25\\output\\A_path.exe',
                    input=input_io,
                    std_program='D:\\src\\3.25\\output\\std.exe')
