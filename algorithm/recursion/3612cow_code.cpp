#include <bits/stdc++.h>
using namespace std;

long long l, n, t;
char str[40];

signed main()
{
    scanf("%s%lld", str + 1, &n);
    l = t = strlen(str + 1);
    while (t < n)
        t <<= 1;
    while (t != l)
    {
        t >>= 1;
        if (n > t)
            if (t + 1 == n)
                n = t;
            else
                n -= t + 1;
    }
    putchar(str[n]);
    return 0;
}