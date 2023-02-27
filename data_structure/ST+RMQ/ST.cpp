#include <bits/stdc++.h>
using namespace std;

const int logn = 20; // 适配于1e5区间长度
const int MAX = 1e5 + 10;
int n, m, st[MAX][logn + 1], lg2[MAX + 1];

inline int read()
{
    int x = 1, k = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();

    while (c >= '0' && c <= '9')
        k = k * 10 + c - '0', c = getchar();
    return x * k;
}

inline void pre() // 初始化log数组
{
    lg2[1] = 0;
    lg2[2] = 1;
    for (int i = 3; i < MAX; i++)
    {
        lg2[i] = lg2[i / 2] + 1;
    }
}
inline void init()
{
    for (int l = 1; (1 << l) <= n; l++) // 相当于区间长度，终止条件亦可写为 l <= logn
        for (int i = 1; i + (1 << l) - 1 <= n; i++)
            st[i][l] = max(st[i][l - 1], st[i + (1 << (l - 1))][l - 1]);
}
inline int query(int l, int r)
{
    /*  方法一： int k = log2(r - l + 1);
        方法二： lg[i] = lg[i / 2] + 1;
        方法三： int k = 31 - __builtin_clz(i); */
    int k = lg2[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main()
{
    n = read(), m = read();
    for (register int i = 1; i <= n; i++)
        st[i][0] = read();

    pre();
    init();
    for (register int i = 1, x, y; i <= m; i++)
    {
        x = read(), y = read();
        int k = lg2[y - x + 1];
        printf("%d\n", max(st[x][k], st[y - (1 << k) + 1][k]));
    }
    return 0;
}
