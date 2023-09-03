#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205;
int n, s[N], f[N][N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i], s[n + i] = s[i];
    for (int i = 2; i <= n; i++)
        for (int l = 1; l <= 2 * n - i + 1; l++) {
            int r = l + i - 1;
            for (int k = l; k < r; k++)
                f[l][r] = max(f[l][r], f[l][k] + f[k + 1][r] +
                                           s[l] * s[k + 1] * s[r + 1]);
        }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, f[i][i + n - 1]);
    cout << ans;
    return 0;
}