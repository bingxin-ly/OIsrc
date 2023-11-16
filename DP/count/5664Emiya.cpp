#include <bits/stdc++.h>
using namespace std;

constexpr int N = 109, M = 2009, MOD = 998244353;
int n, m, a[N][M];
long long f[N][N << 1], ans = 1;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cin >> a[i][j], (a[i][0] += a[i][j]) %= MOD;
        (ans *= a[i][0] + 1) %= MOD;
    }
    (ans += MOD - 1) %= MOD;
    for (int o = 1; o <= m; o++) {
        f[0][n] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = -i + n; j <= i + n; j++) {
                f[i][j] = f[i - 1][j];
                (f[i][j] += f[i - 1][j - 1] * a[i][o]) %= MOD;
                (f[i][j] += f[i - 1][j + 1] * (a[i][0] - a[i][o] + MOD)) %= MOD;
            }
        for (int j = 1; j <= n; j++)
            (ans += MOD - f[n][j + n]) %= MOD;
    }
    cout << ans;
    return 0;
}