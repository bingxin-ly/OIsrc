#include <bits/stdc++.h>
using namespace std;
typedef long long loong;

inline int input()
{
    int o = 1, p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            o = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0',
        c = getchar();
    return o * p;
}

const int N = 5e3 + 10;
int arr[N];

loong process(int a, int b)
{
    loong cnt = 0;
    for (int i = a; i <= b - 2; i++)
        for (int j = i + 1; j <= b - 1; j++)
            for (int k = j + 1; k <= b; k++)
                if (arr[i] + arr[j] + arr[k] == 0)
                    cnt++;
    return cnt;
}

int main()
{
    int n = input(), q = input();
    for (int i = 1; i <= n; i++)
        arr[i] = input();
    for (int i = 1; i <= q; i++)
    {
        int a = input(), b = input();
        printf("%lld\n", process(a, b));
    }
    return 0;
}