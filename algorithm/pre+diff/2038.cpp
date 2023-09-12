#include <bits/stdc++.h>
using namespace std;

constexpr int N = 130;
int d, n, w[N][N];
signed main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\src\\.in", "r", stdin);
    freopen("D:\\src\\.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> d >> n;
    for (int i = 1, x, y; i <= n; i++) cin >> x >> y >> w[++x][++y];
    for (int x = 1; x <= 129; x++)
        for (int y = 1; y <= 129; y++)
            w[x][y] += w[x - 1][y] + w[x][y - 1] - w[x - 1][y - 1];

    int ans = 0, cnt = 0;

    for (int x = 1; x <= 129; x++)
        for (int y = 1; y <= 129; y++) {
            int x2 = min(x + d, 129), y2 = min(y + d, 129);
            int x1 = max(x - d - 1, 0), y1 = max(y - d - 1, 0);
            int val = w[x2][y2] - w[x2][y1] - w[x1][y2] + w[x1][y1];
            if (val > ans)
                cnt = 1, ans = val;
            else if (val == ans)
                cnt += 1;
        }

    cout << cnt << ' ' << ans;
    return 0;
}