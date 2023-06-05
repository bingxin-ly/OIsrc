#include <bits/stdc++.h>
using namespace std;

/* 动态规划做法, 状转方程：
if (a[i][j] == 1)
    f[i][j] = min({f[i][j - 1], f[i - 1][j], f[i - 1][j - 1]}) + 1;
    因为要保险四周都是没有 0 的，所以取 min */
const int N = 110;
int sum[N][N];

int calc(int x1, int y1, int x2, int y2)
{
    return sum[x2][y2] -
           sum[x1 - 1][y2] - sum[x2][y1 - 1] +
           sum[x1 - 1][y1 - 1];
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> sum[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];

    for (int l = min(n, m); l >= 1; l--)
        for (int i = 1; i <= n - l + 1; i++)
            for (int j = 1; j <= m - l + 1; j++)
                if (calc(i, j, i + l - 1, j + l - 1) == l * l)
                    cout << l, exit(0);
    cout << 0;
    return 0;
}