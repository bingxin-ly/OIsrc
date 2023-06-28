#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int n, m, k, w[N][N];
int huge[N][N], tiny[N][N]; // 常用写法写混了，从此 huge / tiny

void handle(int a[], int b[], int len, function<bool(int, int)> cmp)
{
    int hh = 0, tt = -1, q[N]{};
    for (int i = 1; i <= len; i++)
    {
        if (hh <= tt && q[hh] <= i - k)
            hh++;
        while (hh <= tt && cmp(a[q[tt]], a[i]))
            tt--;
        q[++tt] = i, b[i] = a[q[hh]];
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> w[i][j];

    auto fmin = [](auto x, auto y)
    { return x >= y; };
    auto fmax = [](auto x, auto y)
    { return x <= y; };
    for (int i = 1; i <= n; i++)
    {
        handle(w[i], tiny[i], m, fmin);
        handle(w[i], huge[i], m, fmax);
    }

    int res = INT_MAX, a[N], b[N], c[N];
    for (int i = k; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
            a[j] = tiny[j][i]; // 把每一行这一列扣下来
        handle(a, b, n, fmin);
        for (int j = 1; j <= n; j++)
            a[j] = huge[j][i];
        handle(a, c, n, fmax);

        for (int j = k; j <= n; j++)
            res = min(res, c[j] - b[j]);
    }
    cout << res;
    return 0;
}