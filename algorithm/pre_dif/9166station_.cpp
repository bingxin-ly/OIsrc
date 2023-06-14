#include <bits/stdc++.h>
using namespace std;

inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0',
        c = getchar();
    return p;
}
inline void write(int x)
{
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int diff[200010], cans[200010], rails[200010], tmp[200010];
int main()
{
    int n = read(), m = read(), x = read();
    for (int i = 1; i <= m; i++)
    {
        int u = read(), v = read();
        diff[u <= x ? u : u + 1]++, diff[v >= x ? v + 1 : v]--;
        if (v > x)
            cans[v] = true;
        if (u < x)
            cans[u] = true;
    }
    for (int i = 1; i <= n; i++)
        rails[i] = rails[i - 1] + diff[i];
    int top = 0;
    for (int i = x; i >= 1; i--)
        if (!rails[i])
            break;
        else if (cans[i])
            tmp[++top] = i;
    while (top > 0)
        write(tmp[top--]), putchar(' ');
    for (int i = x + 1; i <= n; i++)
        if (!rails[i])
            break;
        else if (cans[i])
            write(i), putchar(' ');
    return 0;
}
