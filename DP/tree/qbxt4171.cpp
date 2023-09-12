#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 5, MOD = 998244353;
int n, pre[N], suf[N], f[N][2];
vector<pair<int, int> > g[N];

void dp(int u, int p) {
    sort(g[u].begin(), g[u].end());
    for (auto pr : g[u])
        if (pr.second != p) dp(pr.second, u);

    int fa = -1, sz = g[u].size();
    for (int i = 0; i < sz; i++)
        if (g[u][i].second == p) fa = i;
    pre[0] = 1;
    for (int i = 0; i < sz; i++) {
        int v = g[u][i].second;
        if (i == fa)
            pre[i + 1] = pre[i];
        else
            pre[i + 1] = 1ll * pre[i] * f[v][1] % MOD;
    }
    suf[sz] = 1;
    for (int i = sz - 1; i >= 0; i--) {
        int v = g[u][i].second;
        if (i == fa)
            suf[i] = suf[i + 1];
        else
            suf[i] = 1ll * suf[i + 1] * f[v][0] % MOD;
    }

    for (int i = 0; i <= sz; i++) {
        (f[u][i <= fa] += 1ll * pre[i] * suf[i] % MOD) %= MOD;
    }
}
signed main() {
    freopen("direction.in", "r", stdin);
    freopen("direction.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(i, v), g[v].emplace_back(i, u);
    dp(1, 0);
    cout << f[1][0];
    return 0;
}