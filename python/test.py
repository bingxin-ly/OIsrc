p = input().lower()
str = input().lower().split()
ans = str.count(p)
if ans:
    cnt = 0
    for i in str:
        if i.startswith(p):
            print(ans, cnt + 1)
            exit(0)
        else:
            cnt += len(i) + 1
else:
    print(-1)
