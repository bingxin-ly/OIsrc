#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, to[N], val[N];
vector<tuple<int, int, int>> tr[N];

namespace hld
{
    int fa[N], dep[N], siz[N], son[N];
    void dfs1(int u, int p)
    {
        fa[u] = p, dep[u] = dep[p] + 1, siz[u] = 1;
        for (const auto &[v, w, id] : tr[u])
            if (v != p)
            {
                to[id] = v, val[v] = w;
                dfs1(v, u);
                siz[u] += siz[v];
                if (siz[v] > siz[son[u]])
                    son[u] = v;
            }
    }
    int tim, dfn[N], rnk[N], top[N];
    void dfs2(int u, int t)
    {
        dfn[u] = ++tim, rnk[tim] = u, top[u] = t;
        if (!son[u])
            return;
        dfs2(son[u], t);
        for (const auto &[v, w, _] : tr[u])
            if (v != fa[u] && v != son[u])
                dfs2(v, v);
    }
}

namespace segtr
{
#define ls (p << 1)
#define rs (p << 1 | 1)
    struct
    {
        int mxn, add, cov;
    } t[N << 2];

    inline void pushup(int p) { t[p].mxn = max(t[ls].mxn, t[rs].mxn); }
    inline void pushdown(int p)
    {
        if (t[p].cov)
        {
            t[ls].mxn = t[rs].mxn = t[p].cov;
            t[ls].cov = t[rs].cov = t[p].cov;
            t[ls].add = t[rs].add = t[p].cov = 0;
        }
        if (t[p].add)
        {
            t[ls].mxn += t[p].add, t[rs].mxn += t[p].add;
            t[ls].add += t[p].add, t[rs].add += t[p].add;
            t[p].add = 0;
        }
    }
    void build(int p, int l, int r)
    {
        if (l == r)
            return t[p].mxn = val[hld::rnk[l]], void();
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        pushup(p);
    }
    void update(int p, int l, int r, int x, int v)
    {
        if (l == r)
            return t[p].mxn = v, void();
        pushdown(p);
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(ls, l, mid, x, v);
        else
            update(rs, mid + 1, r, x, v);
        pushup(p);
    }
    void cover(int p, int l, int r, int ql, int qr, int v)
    {
        if (ql <= l && r <= qr)
            return t[p].mxn = t[p].cov = v, t[p].add = 0, void();
        pushdown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            cover(ls, l, mid, ql, qr, v);
        if (qr > mid)
            cover(rs, mid + 1, r, ql, qr, v);
        pushup(p);
    }
    void increase(int p, int l, int r, int ql, int qr, int v)
    {
        if (ql <= l && r <= qr)
            return t[p].mxn += v, t[p].add += v, void();
        pushdown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            increase(ls, l, mid, ql, qr, v);
        if (qr > mid)
            increase(rs, mid + 1, r, ql, qr, v);
        pushup(p);
    }
    int querymax(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return t[p].mxn;
        pushdown(p);
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid)
            res = max(res, querymax(ls, l, mid, ql, qr));
        if (qr > mid)
            res = max(res, querymax(rs, mid + 1, r, ql, qr));
        return res;
    }
}

using namespace hld;
using namespace segtr;
void change(int k, int w) { update(1, 1, n, dfn[to[k]], w); }
void pathcover(int u, int v, int w)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        cover(1, 1, n, dfn[top[u]], dfn[u], w);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    if (u != v)
        cover(1, 1, n, dfn[u] + 1, dfn[v], w);
}
void pathplus(int u, int v, int w)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        increase(1, 1, n, dfn[top[u]], dfn[u], w);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    if (u != v)
        increase(1, 1, n, dfn[u] + 1, dfn[v], w);
}
int pathmax(int u, int v)
{
    int res = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        res = max(res, querymax(1, 1, n, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    if (u != v)
        res = max(res, querymax(1, 1, n, dfn[u] + 1, dfn[v]));
    return res;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w,
            tr[u].emplace_back(v, w, i), tr[v].emplace_back(u, w, i);

    dfs1(1, 0), dfs2(1, 1), build(1, 1, n);
    char op[10];
    int u, v, k, w;
    while (cin >> op)
        switch (op[1])
        {
        case 'h':
            cin >> k >> w;
            change(k, w);
            break;
        case 'o':
            cin >> u >> v >> w;
            pathcover(u, v, w);
            break;
        case 'd':
            cin >> u >> v >> w;
            pathplus(u, v, w);
            break;
        case 'a':
            cin >> u >> v;
            cout << pathmax(u, v) << '\n';
            break;
        case 't':
            return 0;
        }
    return 0;
}