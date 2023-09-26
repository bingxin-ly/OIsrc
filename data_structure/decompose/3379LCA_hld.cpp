#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, m, s;
vector<int> g[N];

int fa[N], dep[N], siz[N], son[N];
void dfs1(int u, int p) {
    fa[u] = p, dep[u] = dep[p] + 1, siz[u] = 1;
    for (int v : g[u])
        if (v != p) {
            dfs1(v, u), siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
}
int top[N];
void dfs2(int u, int t) {
    top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int v : g[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}
int lca(int u, int v) {
    while (top[u] != top[v])
        if (dep[top[u]] > dep[top[v]])
            u = fa[top[u]];
        else
            v = fa[top[v]];
    return dep[u] > dep[v] ? v : u;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    dfs1(s, 0), dfs2(s, s);
    for (int x, y; m--;)
        cin >> x >> y, cout << lca(x, y) << '\n';
    return 0;
}