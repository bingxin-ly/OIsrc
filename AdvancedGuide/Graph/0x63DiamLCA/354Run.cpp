#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 9;
int n, m, w[N], s[N], t[N];
vector<int> g[N];
vector<pair<int, int> > q[N];

int p[N], vis[N], fa[N], dep[N], lca[N];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
void tarjan(int u) {
    vis[u] = 1;
    for (int v : g[u])
        if (!vis[v]) fa[v] = u, dep[v] = dep[u] + 1, tarjan(v), p[v] = u;
    for (const auto &[v, i] : q[u])
        if (vis[v] == 2 || v == u) lca[i] = find(v);
    vis[u] = 2;
}

struct opr {
    int pos, val, tag;
};
vector<opr> o[N];
int c[2][N << 1], ans[N];
void dfs(int u) {
    int v0 = c[0][w[u] + dep[u]], v1 = c[1][w[u] - dep[u] + n];
    for (int v : g[u])
        if (dep[v] > dep[u]) dfs(v);
    for (opr op : o[u]) c[op.tag][op.pos] += op.val;
    ans[u] = c[0][w[u] + dep[u]] - v0 + c[1][w[u] - dep[u] + n] - v1;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i <= m; i++)
        cin >> s[i] >> t[i],
            q[s[i]].emplace_back(t[i], i), q[t[i]].emplace_back(s[i], i);
    iota(p + 1, p + n + 1, 1), tarjan(1);

    for (int i = 1; i <= m; i++) {
        o[s[i]].push_back({dep[s[i]], 1, 0});
        o[fa[lca[i]]].push_back({dep[s[i]], -1, 0});
        o[t[i]].push_back({dep[s[i]] - 2 * dep[lca[i]] + n, 1, 1});
        o[lca[i]].push_back({dep[s[i]] - 2 * dep[lca[i]] + n, -1, 1});
    }
    dfs(1);
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    return 0;
}