#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 5;
int n, m;
vector<int> g[N];

int fr[N], rt;
void ring(int u, int p) {
    if (fr[u]) return fr[rt = u] = p, void();
    fr[u] = p;
    for (int v : g[u])
        if (v != p && !rt) ring(v, u);
}

vector<int> res;
int rng[N], vis[N], opt, mxn = n + 1;
void solve(int u) {
    res.emplace_back(u), vis[u] = 1;
    if (rng[u]) {
        bool flag = false;
        for (int v : g[u]) {
            if (opt) break;
            if (vis[v]) continue;
            if (rng[v]) {
                size_t p = upper_bound(g[u].begin(), g[u].end(), v) - g[u].begin();
                while (p < g[u].size() && vis[g[u][p]]) p++;
                if (p != g[u].size())
                    mxn = g[u][p];
                else if (v > mxn)
                    flag = 1, opt = 1;
                break;
            }
        }
        for (int v : g[u]) {
            if (vis[v] || (rng[v] && flag)) continue;
            solve(v);
        }
    } else {
        for (int v : g[u])
            if (!vis[v]) solve(v);
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end());
    if (m < n) {
        function<void(int, int)> dfs = [&](int u, int p) {
            res.emplace_back(u);
            for (int v : g[u])
                if (v != p) dfs(v, u);
        };
        dfs(1, 0);
    } else {
        ring(1, 0);
        int p = rt;
        do rng[p] = 1, p = fr[p];
        while (p != rt);
        solve(1);
    }
    for (int i : res) cout << i << ' ';
    return 0;
}