#include <bits/stdc++.h>
using namespace std;

constexpr int N = 21;
long long n, m, vis[N], f[N][N][2];

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    f[1][1][0] = f[1][1][1] = 1;
    for (int i = 2; i <= 20; i++)
        for (int j = 1; j <= i; j++) {
            for (int p = j; p <= i - 1; p++) f[i][j][0] += f[i - 1][p][1];
            for (int p = 1; p <= j - 1; p++) f[i][j][1] += f[i - 1][p][0];
        }
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        memset(vis, 0, sizeof(vis));
        int lst, pos;
        for (int j = 1; j <= n; j++) {
            if (f[n][j][1] >= m) {
                lst = j, pos = 1;
                break;
            } else
                m -= f[n][j][1];
            if (f[n][j][0] >= m) {
                lst = j, pos = 0;
                break;
            } else
                m -= f[n][j][0];
        }
        vis[lst] = 1, cout << lst;
        for (int i = 2; i <= n; i++) {
            pos ^= 1;
            for (int len = 1, rnk = 0; len <= n; len++) {
                if (vis[len]) continue;
                rnk++;
                if (pos == 0 && len < lst || pos == 1 && len > lst) {
                    if (f[n - i + 1][rnk][pos] >= m) {
                        lst = len;
                        break;
                    } else
                        m -= f[n - i + 1][rnk][pos];
                }
            }
            vis[lst] = 1, cout << ' ' << lst;
        }
        cout << '\n';
    }
    return 0;
}