from math import gcd, lcm
n = 1000
file = open('ans.txt', 'w')


def f(n):
    res = 0
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            for k in range(1, n + 1):
                if i + j + k == n:
                    res += lcm(i, gcd(j, k)) % 998244353
    with open(f'ans/{n}', 'w') as file:
        file.write(str(res) + ',')
    return


for i in range(1, n + 1):
    try:
        with open(f'./ans/{i}', 'r') as tmp:
            file.write(tmp.readline().strip())
    except FileNotFoundError:
        print(f'{i} not found')
        f(i)
