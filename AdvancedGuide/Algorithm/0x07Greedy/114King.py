n = int(input())
p = []
mul = int(input().split()[0])
ans = 0
for _ in range(n):
    a, b = map(int, input().split())
    p.append((a, b))

p.sort(key=lambda x: x[0] * x[1])
for i in p:
    ans = max(ans, mul // i[1])
    mul *= i[0]
print(ans)
