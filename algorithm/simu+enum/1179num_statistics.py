l, r = map(int, input().split())
cnt = 0
for i in range(l, r + 1):
    for c in str(i):
        cnt += c == '2'
print(cnt)