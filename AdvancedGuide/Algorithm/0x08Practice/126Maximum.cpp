#include <bits/stdc++.h>
using namespace std;

constexpr int N = 109;
int n, a[N][N], b[N], f[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j], a[i][j] += a[i - 1][j];
    int ans = -127;
    for (int p = 1; p <= n; p++)
        for (int q = p; q <= n; q++) {
            for (int i = 1; i <= n; i++) b[i] = a[q][i] - a[p - 1][i];
            for (int i = 1; i <= n; i++) f[i] = f[i - 1] > 0 ? f[i - 1] + b[i] : b[i];
            for (int i = 1; i <= n; i++) ans = max(ans, f[i]);
        }
    cout << ans;
    return 0;
}