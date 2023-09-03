#include <bits/stdc++.h>
using namespace std;

constexpr int N = 11;
int n, m, k, w[N][N];
double avg, f[N][N][N][N][N];
double squ(double $) { return $ * $; }
int sum(int u, int d, int l, int r) {
    return w[d][r] - w[d][l - 1] - w[u - 1][r] + w[u - 1][l - 1];
}

double dp(int u, int d, int l, int r, int k) {
    if (f[u][d][l][r][k]) return f[u][d][l][r][k];
    if (k == 1) return f[u][d][l][r][k] = squ(sum(u, d, l, r) - avg);
    f[u][d][l][r][k] = 1e9;
    for (int i = u; i < d; i++)
        for (int j = 1; j < k; j++) {
            f[u][d][l][r][k] =
                min(f[u][d][l][r][k],
                    dp(u, i, l, r, j) + dp(i + 1, d, l, r, k - j));
        }
    for (int i = l; i < r; i++)
        for (int j = 1; j < k; j++) {
            f[u][d][l][r][k] =
                min(f[u][d][l][r][k],
                    dp(u, d, l, i, j) + dp(u, d, i + 1, r, k - j));
        }
    return f[u][d][l][r][k];
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> w[i][j],
                w[i][j] += w[i - 1][j] + w[i][j - 1] - w[i - 1][j - 1];
    avg = 1.0 * w[n][m] / k;
    cout << fixed << setprecision(2) << sqrt(dp(1, n, 1, m, k) / k);
    return 0;
}