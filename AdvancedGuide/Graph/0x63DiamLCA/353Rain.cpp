#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, x[N], y[N], z[N];
vector<int> g[N];
vector<pair<int, bool> > q[N];

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
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

struct P {
    int num, idx;
    friend bool operator<(const P &x, const P &y) {
        return x.num != y.num ? x.num > y.num : x.idx < y.idx;
    }
};
set<P> obj;
int cnt[N], ans[N];
void modify(int u, int x) {
    if (x > 0)
        for (auto p = q[u].begin(); p != q[u].end(); p++) {
            int z = p->first, v = p->second;
            obj.erase({cnt[z], z}), cnt[z] += v ? 1 : -1, obj.insert({cnt[z], z});
        }
    else
        for (auto p = q[u].rbegin(); p != q[u].rend(); p++) {
            int z = p->first, v = p->second;
            obj.erase({cnt[z], z}), cnt[z] -= v ? 1 : -1, obj.insert({cnt[z], z});
        }
}
void update(int u) {
    for (auto v = g[u].begin(); v != g[u].end(); v++)
        if (*v != fa[u]) update(*v);
    modify(u, 1);
}
void fallback(int u) {
    modify(u, -1);
    for (auto v = g[u].rbegin(); v != g[u].rend(); v++)
        if (*v != fa[u]) fallback(*v);
}
void dsu(int u, bool keep) {
    for (int v : g[u])
        if (v != fa[u] && v != son[u]) dsu(v, 0);
    if (son[u]) dsu(son[u], 1);

    for (auto it = g[u].begin(); it != g[u].end(); it++) {
        int v = *it;
        if (v != fa[u] && v != son[u]) update(v);
    }
    modify(u, 1), ans[u] = obj.begin()->idx;

    if (!keep) {
        modify(u, -1);
        for (auto it = g[u].rbegin(); it != g[u].rend(); it++) {
            int v = *it;
            if (v != fa[u] && v != son[u]) fallback(v);
        }
        if (son[u]) fallback(son[u]);
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    dfs1(1, 0), dfs2(1, 1);
    for (int i = 1; i <= m; i++) cin >> x[i] >> y[i] >> z[i];
    vector<int> num(z, z + m + 1);
    sort(num.begin(), num.end()), num.erase(unique(num.begin(), num.end()), num.end());
    for (int i = 1; i <= m; i++) {
        z[i] = lower_bound(num.begin(), num.end(), z[i]) - num.begin();
        int ac = lca(x[i], y[i]);
        q[x[i]].emplace_back(z[i], 1), q[y[i]].emplace_back(z[i], 1);
        q[ac].emplace_back(z[i], 0), q[fa[ac]].emplace_back(z[i], 0);
    }
    for (int i = 0; i <= n; i++) obj.insert({0, i});
    dsu(1, 1);
    for (int i = 1; i <= n; i++) cout << num[ans[i]] << '\n';
    return 0;
}