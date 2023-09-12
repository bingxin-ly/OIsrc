#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5, MOD = 10007;
int n, w[N], mxv, ans;
vector<int> g[N];

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    for (int i = 1; i <= n; i++) cin >> w[i];

    for (int u = 1; u <= n; u++) {
        int fir = 0, sec = 0, sum = 0, pro = 0;
        for (int v : g[u]) {
            if (w[v] > fir)
                sec = fir, fir = w[v];
            else if (w[v] > sec)
                sec = w[v];
            (sum += w[v]) %= MOD, (pro += w[v] * w[v]) %= MOD;
        }
        (sum *= sum) %= MOD, (ans += (sum - pro + MOD)) %= MOD;
        mxv = max(mxv, fir * sec);
    }
    cout << mxv << ' ' << ans;
    return 0;
}