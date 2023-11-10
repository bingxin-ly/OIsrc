#include <bits/stdc++.h>
using namespace std;

constexpr int N = 409;
int n, v[N], w[N], f[N][N], g[N][N], h[N][N], dp[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 1; i <= n; i++) cin >> w[i];
    memset(f, ~0x3f, sizeof(f)), memset(g, ~0x3f, sizeof(g)), memset(h, ~0x3f, sizeof(h));
    for (int i = n; i; i--) {
        f[i][i] = v[1], g[i][i] = h[i][i] = 0;
        for (int j = i + 1; j <= n; j++) {
            for (int k = i; k < j - 1; k++)
                if (w[k] + 1 == w[j]) g[i][j] = max(g[i][j], g[i][k] + f[k + 1][j - 1]);
            if (w[j - 1] + 1 == w[j]) g[i][j] = max(g[i][j], g[i][j - 1]);
        }
        for (int j = i + 1; j <= n; j++) {
            for (int k = i; k < j - 1; k++)
                if (w[k] - 1 == w[j]) h[i][j] = max(h[i][j], h[i][k] + f[k + 1][j - 1]);
            if (w[j - 1] - 1 == w[j]) h[i][j] = max(h[i][j], h[i][j - 1]);
        }
        for (int j = i; j <= n; j++) {
            if (1 <= w[j] - w[i] + 1 && w[j] - w[i] + 1 <= n)
                f[i][j] = max(f[i][j], g[i][j] + v[w[j] - w[i] + 1]);
            if (1 <= w[i] - w[j] + 1 && w[i] - w[j] + 1 <= n)
                f[i][j] = max(f[i][j], h[i][j] + v[w[i] - w[j] + 1]);
            for (int k = i; k < j; k++) f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j]);
            for (int k = i + 1; k < j; k++)
                if (1 <= 2 * w[k] - w[i] - w[j] + 1 && 2 * w[k] - w[i] - w[j] + 1 <= n)
                    f[i][j] = max(f[i][j], g[i][k] + h[k][j] + v[2 * w[k] - w[j] - w[i] + 1]);
        }
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        for (int j = 0; j < i; j++) dp[i] = max(dp[i], dp[j] + f[j + 1][i]);
    }
    cout << dp[n];
    return 0;
}