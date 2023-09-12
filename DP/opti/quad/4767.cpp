#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3005;
int n, m, p[N], s[N], f[N], g[N];
struct {
    int p, l, r;
} q[N];
int calc(int k, int j) {
    int o = (k + j + 1) >> 1;
    int pre = p[o] * (o - k) - (s[o] - s[k]);
    int suf = (s[j] - s[o]) - p[o] * (j - o);
    return g[k] + pre + suf;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> p[i], s[i] = s[i - 1] + p[i];

    memset(g, 0x3f, sizeof(g)), g[0] = 0;
    for (int i = 1; i <= m; i++) {
        int l = 1, r = 1;
        q[1] = {0, 1, n};
        for (int j = 1; j <= n; j++) {
            if (q[l].r == j - 1) l++;
            f[j] = calc(q[l].p, q[l].l = j);
            while (l <= r && calc(j, q[r].l) <= calc(q[r].p, q[r].l)) r--;
            int L = q[r].l + 1, R = n + 1;
            while (L < R) {
                int s = (L + R) >> 1;
                (calc(j, s) <= calc(q[r].p, s) ? R = s : L = s + 1);
            }
            if (L > n) continue;
            q[r].r = L - 1, q[++r] = {j, L, n};
        }
        memcpy(g, f, sizeof(f));
    }
    cout << f[n];
    return 0;
}