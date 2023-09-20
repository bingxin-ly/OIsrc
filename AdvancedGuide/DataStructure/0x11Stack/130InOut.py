from math import factorial

n = int(input())
A = factorial(2 * n)
B = factorial(n)
print(A // B // B // (n + 1))
