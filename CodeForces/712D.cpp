#include <bits/stdc++.h>
using namespace std;

constexpr int N = 4e5 + 1009, M = 1e9 + 7;
int a, b, k, t, n, f[N], s[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> a >> b >> k >> t, n = 2 * k * t, f[n] = 1;
    for (int i = 1; i <= 2 * t; i++) {
        s[0] = f[0];
        for (int j = 1; j <= 2 * n + k; j++) s[j] = (s[j - 1] + f[j]) % M;
        for (int j = 0; j <= k; j++) f[j] = s[j + k];
        for (int j = k + 1; j <= 2 * n; j++) f[j] = (s[j + k] - s[j - k - 1] + M) % M;
    }
    int ans = 0;
    for (int i = n - a + b + 1; i <= 2 * n; i++) (ans += f[i]) %= M;
    cout << ans;
    return 0;
}