a, b, c = map(int, input())
if a + b + c <= 100 and b % 5 == 0 and c % 7 == 0 and a-  b > b - c:
    print("Yes")
else:
    print("No")