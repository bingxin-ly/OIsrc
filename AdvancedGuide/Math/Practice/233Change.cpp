#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2009, V = 309;
int n, m, v, e, a[N], b[N], w[V][V];
double p[N], f[N][N][2];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> v >> e;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) cin >> p[i];
    memset(w, 0x3f, sizeof(w));
    for (int i = 1; i <= v; i++) w[i][i] = 0;
    for (int i, j, k; e--;) cin >> i >> j >> k, w[i][j] = w[j][i] = min(w[i][j], k);
    for (int k = 1; k <= v; k++)
        for (int i = 1; i <= v; i++)
            for (int j = 1; j <= v; j++) w[i][j] = min(w[i][j], w[i][k] + w[k][j]);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) f[i][j][0] = f[i][j][1] = 1e10;
    f[1][0][0] = f[1][1][1] = 0;
    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= i && j <= m; j++) {
            f[i][j][0] =
                min(f[i - 1][j][0] +
                        w[a[i - 1]][a[i]],
                    f[i - 1][j][1] +
                        w[b[i - 1]][a[i]] * p[i - 1] +
                        w[a[i - 1]][a[i]] * (1 - p[i - 1]));
            if (j)
                f[i][j][1] =
                    min(f[i - 1][j - 1][0] +
                            w[a[i - 1]][b[i]] * p[i] +
                            w[a[i - 1]][a[i]] * (1 - p[i]),
                        f[i - 1][j - 1][1] +
                            w[b[i - 1]][b[i]] * p[i - 1] * p[i] +
                            w[a[i - 1]][b[i]] * (1 - p[i - 1]) * p[i] +
                            w[b[i - 1]][a[i]] * p[i - 1] * (1 - p[i]) +
                            w[a[i - 1]][a[i]] * (1 - p[i - 1]) * (1 - p[i]));
        }
    double ans = 1e10;
    for (int j = 0; j <= m; j++) ans = min(ans, min(f[n][j][0], f[n][j][1]));
    cout << fixed << setprecision(2) << ans;
    return 0;
}