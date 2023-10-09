n = int(input())
f = [1] + [0] * 500
for i in range(1, n + 1):
    for j in range(1, i + 1):
        f[i] += f[j - 1] * f[i - j]
print(f[n])