// A - B = C 三指针 & 二分 & 哈希
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

signed main()
{
    int n(read()), a[n + 1], c(read());
    for_each(a + 1, a + n + 1, [](int &x)
             { x = read(); });
    sort(a + 1, a + n + 1);
    long long ans(0);
    for (int i(1), j(1), k(1); i <= n; i++)
    {
        while (j <= n && a[j] - a[i] < c)
            j++;
        while (k <= n && a[k] - a[i] <= c)
            k++;
        assert(k >= 2);
        if (a[j] - a[i] == c && a[k - 1] - a[i] == c) // 此时 j 和 k 可能都跑出去力
            ans += k - j;
    }
    printf("%lld", ans);
    return 0;
}