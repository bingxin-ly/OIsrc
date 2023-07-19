#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

constexpr int N = 5e5 + 5;
int n, m, a;
vector<int> g[N];

int fa[N], dep[N], siz[N], son[N];
void dfs1(int u, int p)
{
    fa[u] = p, dep[u] = dep[p] + 1, siz[u] = 1;
    for (int v : g[u])
        if (v != p)
        {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
}
int tim, dfn[N], top[N];
void dfs2(int u, int t)
{
    dfn[u] = ++tim, top[u] = t;
    if (!son[u])
        return;
    dfs2(son[u], t);
    for (int v : g[u])
        if (v != fa[u] && v != son[u])
            dfs2(v, v);
}
int lca(int u, int v)
{
    while (top[u] != top[v])
        if (dep[top[u]] > dep[top[v]])
            u = fa[top[u]];
        else
            v = fa[top[v]];
    return dep[u] > dep[v] ? v : u;
}

namespace fenwick
{
    long long t[N];
    inline int lowbit(int x) { return x & -x; }
    inline void _add(int p, int v)
    {
        for (; p <= n; p += lowbit(p))
            t[p] += v;
    }
    inline void cover(int l, int r) { _add(l, 1), _add(r + 1, -1); }
    inline long long query(int p)
    {
        long long ret = 0;
        for (; p; p -= lowbit(p))
            ret += t[p];
        return ret;
    }
}

void modify(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        fenwick::cover(dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    fenwick::cover(dfn[u], dfn[v]);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> a;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    dfs1(a, 0), dfs2(a, a);

    long long ans = 0, p = a;
    for (int i = 0, c; i < m; i++)
    {
        cin >> c;
        if (fenwick::query(dfn[c]))
            continue;
        modify(p, c);
        ans += dep[p] + dep[c] - dep[lca(p, c)] * 2;
        p = c;
    }
    cout << ans;
    return 0;
}