#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 9;
int n, m;
vector<int> g[N];
vector<pair<int, int> > q[N];

int p[N];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

int u[N], v[N], vis[N], lca[N];
void tarjan(int u) {
    vis[u] = 1;
    for (int v : g[u])
        if (!vis[v]) tarjan(v), p[v] = u;
    for (const auto &[v, i] : q[u])
        if (vis[v] == 2 || v == u) lca[i] = find(v);
    vis[u] = 2;
}

int f[N];
void dfs(int u) {
    vis[u] = 0;
    for (int v : g[u])
        if (vis[v]) dfs(v), f[u] += f[v];
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i];
        q[u[i]].emplace_back(v[i], i), q[v[i]].emplace_back(u[i], i);
    }
    iota(p + 1, p + n + 1, 1), tarjan(1);
    for (int i = 1; i <= m; i++)
        f[u[i]] += 1, f[v[i]] += 1, f[lca[i]] -= 2;
    dfs(1);
    int ans = 0;
    for (int i = 2; i <= n; i++)
        if (f[i] < 2) ans += f[i] ? 1 : m;
    cout << ans;
    return 0;
}