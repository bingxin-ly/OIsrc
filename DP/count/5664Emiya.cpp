#include <bits/stdc++.h>
using namespace std;

constexpr int N = 109, M = 2009, MOD = 998244353;
int n, m, a[N][M], s[N][M];
long long f[N][N << 1], g[N][N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j], (s[i][0] += a[i][j]) %= MOD;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            s[i][j] = (s[i][0] - a[i][j] + MOD) % MOD;
    long long ans = 0;
    for (int c = 1; c <= m; c++) {
        memset(f, 0, sizeof(f)), f[0][n] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = n - i; j <= n + i; j++)
                f[i][j] = (f[i - 1][j] +
                           f[i - 1][j - 1] * a[i][c] % MOD +
                           f[i - 1][j + 1] * s[i][c] % MOD) %
                          MOD;
        for (int j = 1; j <= n; j++)
            (ans += f[n][n + j]) %= MOD;
    }
    g[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= n; j++)
            g[i][j] = (g[i - 1][j] +
                       (j ? g[i - 1][j - 1] * s[i][0] % MOD : 0)) %
                      MOD;
    for (int j = 1; j <= n; j++)
        (ans -= g[n][j]) %= MOD;
    cout << (ans + MOD) % MOD * (MOD - 1) % MOD;
    return 0;
}