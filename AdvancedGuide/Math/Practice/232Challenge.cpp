#include <bits/stdc++.h>
using namespace std;

constexpr int N = 209;
int n, l, k, a[N];
double p[N], f[N][N][N << 1];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> l >> k, k = min(k, n);
    for (int i = 1; i <= n; i++) cin >> p[i], p[i] /= 100;
    for (int i = 1; i <= n; i++) cin >> a[i];

    f[0][0][k + N] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            for (int k = -n + N; k <= n + N; k++) {
                f[i][j + 1][min(k + a[i], n + N)] += p[i] * f[i - 1][j][k];
                f[i][j][k] += (1 - p[i]) * f[i - 1][j][k];
            }
    double ans = 0;
    for (int j = l; j <= n; j++)
        for (int k = N; k <= n + N; k++) ans += f[n][j][k];
    cout << fixed << setprecision(6) << ans;
    return 0;
}