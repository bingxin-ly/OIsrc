#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, w[N];
vector<int> g[N], val;

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
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

struct
{
    int ls, rs, val;
} t[N << 5];
int idx, rt[N];

void pushup(int p) { t[p].val = t[t[p].ls].val + t[t[p].rs].val; }
void modify(int &p, int l, int r, int x)
{
    t[++idx] = t[p], p = idx;
    if (l == r)
        return t[p].val += 1, void();
    int mid = (l + r) >> 1;
    if (x <= mid)
        modify(t[p].ls, l, mid, x);
    else
        modify(t[p].rs, mid + 1, r, x);
    pushup(p);
}
void build(int u, int p)
{
    modify(rt[u] = rt[p], 1, n, w[u]);
    for (int v : g[u])
        if (v != p)
            build(v, u);
}
int query(int a, int b, int c, int d, int l, int r, int k)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1,
        les = t[t[a].ls].val + t[t[b].ls].val - t[t[c].ls].val - t[t[d].ls].val;
    if (k <= les)
        return query(t[a].ls, t[b].ls, t[c].ls, t[d].ls, l, mid, k);
    else
        return query(t[a].rs, t[b].rs, t[c].rs, t[d].rs, mid + 1, r, k - les);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    val.emplace_back(0);
    for (int i = 1; i <= n; i++)
        cin >> w[i], val.emplace_back(w[i]);
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 1; i <= n; i++)
        w[i] = lower_bound(val.begin(), val.end(), w[i]) - val.begin();
    n = val.size() - 1;
    build(1, 0), dfs1(1, 0), dfs2(1, 1);

    for (int u, v, k, pre = 0; m--;)
    {
        cin >> u >> v >> k, u ^= pre;
        int t = lca(u, v);
        cout << (pre = val[query(rt[u], rt[v], rt[t], rt[fa[t]], 1, n, k)]) << '\n';
    }
    return 0;
}