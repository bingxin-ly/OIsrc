#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m;
vector<pair<int, int> > g[N];
int tim, dfn[N], dep[N], fa[N][18];
long long dis[N];
void dfs(int u, int p) {
    dfn[u] = ++tim, fa[u][0] = p, dep[u] = dep[p] + 1;
    for (const auto &[v, w] : g[u])
        if (v != p) dis[v] = dis[u] + w, dfs(v, u);
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = __lg(n); i >= 0; i--)
        if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    for (int i = __lg(n); i >= 0; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
long long len(int u, int v) { return dis[u] + dis[v] - 2 * dis[lca(u, v)]; }

set<pair<int, int> > s;
int pre(int x) {
    auto it = s.lower_bound({dfn[x], x});
    if (it == s.begin()) it = s.end();
    return (--it)->second;
}
int suf(int x) {
    auto it = s.upper_bound({dfn[x], x});
    if (it == s.end()) it = s.begin();
    return it->second;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    dfs(1, 0);
    for (int i = 1; i <= __lg(n); i++)
        for (int u = 1; u <= n; u++) fa[u][i] = fa[fa[u][i - 1]][i - 1];

    cin >> m;
    char c;
    long long ans = 0;
    for (int i = 1, x; i <= m; i++) {
        cin >> c;
        if (c == '+') {
            cin >> x;
            if (s.size() == 1)
                ans = 2 * len(s.begin()->second, x);
            else if (s.size() > 1) {
                int l = pre(x), r = suf(x);
                ans += len(l, x) + len(x, r) - len(l, r);
            }
            s.emplace(dfn[x], x);
        } else if (c == '-') {
            cin >> x;
            s.erase({dfn[x], x});
            if (s.size() <= 1)
                ans = 0;
            else {
                int l = pre(x), r = suf(x);
                ans -= len(l, x) + len(x, r) - len(l, r);
            }
        } else
            cout << ans / 2 << '\n';
    }
    return 0;
}