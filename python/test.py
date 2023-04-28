with open('D:\src\python\\1') as f:
    lines = f.readlines()
n = int(lines[0])
insert = []
for line in lines[1:]:
    n, m = map(int, line.split())
    if n == 1:
        insert.append(m)
insert.sort()
[print(x) for x in insert]
