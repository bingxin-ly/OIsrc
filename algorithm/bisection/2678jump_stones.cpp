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

int l, n, m, len[50010];
bool check(int x)
{
    int cnt = 0, pre = 0; // 记录前一个点而不是计算
    for (int i = 1; i <= n + 1; i++)
    {
        if (len[i] - len[pre] < x)
            cnt++;
        else
            pre = i;
    }
    return cnt <= m;
}
signed main()
{
    l = read(), n = read(), m = read();
    for (int i = 1; i <= n; i++)
        len[i] = read();
    len[n + 1] = l;
    int left = 1, right = l + 1;
    while (left < right)
    {
        int mid = (left + right) >> 1;
        if (check(mid))
            left = mid + 1;
        else
            right = mid;
    }
    printf("%d", left - 1);
    return 0;
}