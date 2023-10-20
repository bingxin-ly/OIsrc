#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, m;
vector<int> g[N];

int fa[N][20], dep[N];
void dfs(int u, int p) {
    fa[u][0] = p, dep[u] = dep[p] + 1;
    for (int v : g[u])
        if (v != p) dfs(v, u);
}
int lca(int u, int v) {
    if (dep[v] > dep[u]) swap(u, v);
    for (int i = __lg(n); i >= 0; i--)
        if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    for (int i = __lg(n); i >= 0; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    dfs(1, 0);
    for (int i = 1; i <= __lg(n); i++)
        for (int u = 1; u <= n; u++)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];

    for (int a, b, c; m--;) {
        cin >> a >> b >> c;
        int ab = lca(a, b), bc = lca(b, c), ac = lca(a, c);
        int pos, ans;
        if (dep[ab] >= dep[bc] && dep[ab] >= dep[ac])
            pos = ab, ans = dep[a] - dep[ac] + dep[b] - dep[ab] + dep[c] - dep[ac];
        else if (dep[bc] >= dep[ab] && dep[bc] >= dep[ac])
            pos = bc, ans = dep[b] - dep[ab] + dep[c] - dep[bc] + dep[a] - dep[ab];
        else
            pos = ac, ans = dep[a] - dep[ab] + dep[c] - dep[ac] + dep[b] - dep[ab];
        cout << pos << ' ' << ans << '\n';
    }
    return 0;
}