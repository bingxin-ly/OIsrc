#include <bits/stdc++.h>
using namespace std;

constexpr int T = 4e6 + 105;
int n, m, t, q[T], c[T], s[T], f[T];
double slope(int i, int j) {
    return 1.0 * ((f[j] + s[j]) - (f[i] + s[i])) / (c[j] == c[i] ? 1e-9 : c[j] - c[i]);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, tt; i <= n; i++) {
        cin >> tt, t = max(t, tt);
        c[tt] += 1, s[tt] += tt;
    }
    for (int i = 1; i < t + m; i++) c[i] += c[i - 1], s[i] += s[i - 1];
    int l = 1, r = 0;
    for (int i = 0; i < t + m; i++) {
        if (i - m >= 0) {
            while (l < r && slope(q[r - 1], q[r]) >= slope(q[r], i - m)) r--;
            q[++r] = i - m;
        }
        f[i] = c[i] * i - s[i];
        while (l < r && (q[l] <= i - 2 * m || slope(q[l], q[l + 1]) <= i)) l++;
        if (l <= r) f[i] = min(f[i], f[q[l]] + (c[i] - c[q[l]]) * i - (s[i] - s[q[l]]));
    }
    int ans = 1 << 30;
    for (int i = t; i < t + m; i++) ans = min(ans, f[i]);
    cout << ans;
    return 0;
}