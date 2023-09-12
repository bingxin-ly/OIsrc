#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, m;
long long p[N], s[N], f[N], g[N], ans;
struct {
    int p, l, r;
} q[N];
long long calc(int j, int k) {
    int o = (j + k + 1) >> 1;
    long long pre = p[o] * (o - j) - (s[o] - s[j]);
    long long suf = (s[k] - s[o]) - p[o] * (k - o);
    return f[j] + pre + suf;
}
bool dp(long long C) {
    int l = 1, r = 1;
    q[1] = {0, 1, n};
    for (int i = 1; i <= n; i++) {
        if (q[l].r == i - 1) l++;
        f[i] = calc(q[l].p, q[l].l = i) + C;
        g[i] = g[q[l].p] + 1;
        while (l <= r && calc(i, q[r].l) < calc(q[r].p, q[r].l)) r--;
        int L = q[r].l + 1, R = n + 1;
        while (L < R) {
            int o = (L + R) >> 1;
            calc(i, o) < calc(q[r].p, o) ? R = o : L = o + 1;
        }
        if (L > n) continue;
        q[r].r = L - 1, q[++r] = {i, L, n};
    }
    if (g[n] <= m) ans = f[n] - C * m;
    return g[n] <= m;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> p[i], s[i] = s[i - 1] + p[i];
    long long l = 0, r = 1e9;
    while (l <= r) {
        long long o = (l + r) >> 1;
        dp(o) ? r = o - 1 : l = o + 1;
    }
    cout << ans;
    return 0;
}