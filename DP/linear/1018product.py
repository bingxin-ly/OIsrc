n, k = map(int, input().split())
s = input()
f = [[0] * (k + 1) for _ in range(n + 1)]
for i in range(1, n + 1):
    f[i][0] = int(s[0:i])
for l in range(1, k + 1):
    for i in range(l + 1, n + 1):
        for j in range(l, i):
            f[i][l] = max(f[i][l], f[j][l - 1] * int(s[j:i]))
print(f[n][k])
