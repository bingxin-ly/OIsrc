#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 10;
int a[N][N];
int calc(int x1, int y1, int x2, int y2) { return a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1]; }

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int mx = 0, my = 0;
    for (int x, y, v; n--;)
        cin >> x >> y >> v,
            a[++x][++y] = v, mx = max(mx, x), my = max(my, y);

    // 有可能 m 过大
    mx = max(mx, m), my = max(my, m);
    for (int i = 1; i <= mx; i++)
        for (int j = 1; j <= my; j++)
            a[i][j] += a[i - 1][j] + a[i][j - 1] -a[i - 1][j - 1];

    int ans = 0;
    for (int i = 1; i <= mx - m + 1; i++)
        for (int j = 1; j <= my - m + 1; j++)
            ans = max(ans, calc(i, j, i + m - 1, j + m - 1));
    cout << ans;
    return 0;
}