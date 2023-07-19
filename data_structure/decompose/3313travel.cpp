#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, q, w[N], c[N];
vector<int> g[N];

namespace hld
{
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
    void dfs2(int u, int p, int t)
    {
        dfn[u] = ++tim, top[u] = t;
        if (!son[u])
            return;
        dfs2(son[u], u, t);
        for (int v : g[u])
            if (v != p && v != son[u])
                dfs2(v, u, v);
    }
}
namespace segtr
{
    constexpr int S = 2e6;
    struct
    {
        int ls, rs;
        int sum, mxn;
    } t[S];
    int idx, rt[N];
#define ls t[p].ls
#define rs t[p].rs
    inline void pushup(int p)
    {
        t[p].mxn = max(t[ls].mxn, t[rs].mxn);
        t[p].sum = t[ls].sum + t[rs].sum;
    }
    void update(int &p, int l, int r, int x, int v)
    {
        !p && (p = ++idx);
        if (l == r)
            return t[p].sum = t[p].mxn = v, void();
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(ls, l, mid, x, v);
        else
            update(rs, mid + 1, r, x, v);
        pushup(p);
    }
    int querysum(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return t[p].sum;
        int mid = (l + r) >> 1, ret = 0;
        if (ql <= mid)
            ret += querysum(ls, l, mid, ql, qr);
        if (qr > mid)
            ret += querysum(rs, mid + 1, r, ql, qr);
        return ret;
    }
    int querymax(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return t[p].mxn;
        int mid = (l + r) >> 1, ret = 0;
        if (ql <= mid)
            ret = max(ret, querymax(ls, l, mid, ql, qr));
        if (qr > mid)
            ret = max(ret, querymax(rs, mid + 1, r, ql, qr));
        return ret;
    }
#undef ls
#undef rs
}

using namespace hld;
using namespace segtr;
void init()
{
    dfs1(1, 0), dfs2(1, 0, 1);
    for (int i = 1; i <= n; i++)
        update(rt[c[i]], 1, n, dfn[i], w[i]);
}
void change(int x, int s, int t)
{
    update(rt[s], 1, n, dfn[x], 0);
    update(rt[t], 1, n, dfn[x], w[x]);
    c[x] = t;
}
void modify(int x, int v)
{
    update(rt[c[x]], 1, n, dfn[x], v);
    w[x] = v;
}
int pathsum(int u, int v)
{
    int ret = 0, r = rt[c[u]];
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ret += querysum(r, 1, n, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    ret += querysum(r, 1, n, dfn[u], dfn[v]);
    return ret;
}
int pathmax(int u, int v)
{
    int ret = 0, r = rt[c[u]];
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ret = max(ret, querymax(r, 1, n, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    ret = max(ret, querymax(r, 1, n, dfn[u], dfn[v]));
    return ret;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> c[i];
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    init();
    char op[4];
    for (int x, y; q--;)
    {
        cin >> op >> x >> y;
        switch (op[1])
        {
        case 'C':
            change(x, c[x], y);
            break;
        case 'W':
            modify(x, y);
            break;
        case 'S':
            cout << pathsum(x, y) << '\n';
            break;
        case 'M':
            cout << pathmax(x, y) << '\n';
            break;
        }
    }
    return 0;
}