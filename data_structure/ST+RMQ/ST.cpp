#include <bits/stdc++.h>
using namespace std;

const int logn = 18; // 适配于1e5区间长度
const int N = 1e5 + 10;
int n, m, ST[N][logn + 1], lg2[N + 1];

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
    for (int i = 3; i < N; i++)
        lg2[i] = lg2[i / 2] + 1;
    /*  方法一： int k = log2(r - l + 1);
        方法二： lg[i] = lg[i / 2] + 1;
        方法三： int k = 31 - __builtin_clz(i); */
}
inline void init()
{
    for (int l = 1; (1 << l) <= n; l++) // 相当于区间长度，终止条件亦可写为 l <= logn
        for (int i = 1; i + (1 << l) - 1 <= n; i++)
            ST[i][l] = max(ST[i][l - 1], ST[i + (1 << (l - 1))][l - 1]);
}
inline int query(int l, int r)
{
    int k = lg2[r - l + 1];
    return max(ST[l][k], ST[r - (1 << k) + 1][k]);
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        ST[i][0] = read();

    pre();
    init();
    for (int i = 1, x, y; i <= m; i++)
    {
        x = read(), y = read();
        printf("%d\n", query(x, y));
    }
    return 0;
}
