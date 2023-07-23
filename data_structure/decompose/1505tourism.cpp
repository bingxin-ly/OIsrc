// 这道题有一些边转点的
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int n, m, to[N], val[N];
vector<tuple<int, int, int>> tr[N];

namespace hld
{
    int fa[N], dep[N], siz[N], son[N];
    void dfs1(int u, int p)
    {
        fa[u] = p, dep[u] = dep[p] + 1, siz[u] = 1;
        for (const auto &[v, w, i] : tr[u])
            if (v != p)
            {
                dfs1(v, u);
                to[i] = v, val[v] = w;
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
    struct
    {
        int ls, rs;
        int sum, mxn, mnn;
        bool rev;
    } t[N << 1];
    int idx, rt;
#define ls t[p].ls
#define rs t[p].rs
    inline void pushup(int p)
    {
        t[p].sum = t[ls].sum + t[rs].sum;
        t[p].mxn = max(t[ls].mxn, t[rs].mxn);
        t[p].mnn = min(t[ls].mnn, t[rs].mnn);
    }
    inline void pushdown(int p)
    {
        if (t[p].rev)
        {
            t[ls].sum *= -1, swap(t[ls].mxn, t[ls].mnn), t[ls].mxn *= -1, t[ls].mnn *= -1;
            t[rs].sum *= -1, swap(t[rs].mxn, t[rs].mnn), t[rs].mxn *= -1, t[rs].mnn *= -1;
            t[ls].rev ^= 1, t[rs].rev ^= 1, t[p].rev = false;
        }
    }
    void build(int &p, int l, int r)
    {
        p = ++idx;
        if (l == r)
            return t[p].sum = t[p].mxn = t[p].mnn = val[hld::rnk[l]], void();
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        pushup(p);
    }
    void update(int p, int l, int r, int x, int w)
    {
        if (l == r)
            return t[p].sum = t[p].mxn = t[p].mnn = w, void();
        pushdown(p);
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(ls, l, mid, x, w);
        else
            update(rs, mid + 1, r, x, w);
        pushup(p);
    }
    void flip(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            t[p].sum *= -1, swap(t[p].mxn, t[p].mnn), t[p].mxn *= -1, t[p].mnn *= -1;
            t[p].rev ^= 1;
            return;
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            flip(ls, l, mid, ql, qr);
        if (qr > mid)
            flip(rs, mid + 1, r, ql, qr);
        pushup(p);
    }
    int querysum(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return t[p].sum;
        pushdown(p);
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
        pushdown(p);
        int mid = (l + r) >> 1, ret = ~0x3f3f3f3f;
        if (ql <= mid)
            ret = max(ret, querymax(ls, l, mid, ql, qr));
        if (qr > mid)
            ret = max(ret, querymax(rs, mid + 1, r, ql, qr));
        return ret;
    }
    int querymin(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return t[p].mnn;
        pushdown(p);
        int mid = (l + r) >> 1, ret = 0x3f3f3f3f;
        if (ql <= mid)
            ret = min(ret, querymin(ls, l, mid, ql, qr));
        if (qr > mid)
            ret = min(ret, querymin(rs, mid + 1, r, ql, qr));
        return ret;
    }
}

using namespace hld;
using namespace segtr;
void updver(int i, int w)
{
    int u = to[i];
    update(rt, 1, n, dfn[u], w);
}
void opposite(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        flip(rt, 1, n, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    // 因为我们边转过点，所以其实lca的值不应该动！
    if (u != v)
        flip(rt, 1, n, dfn[u] + 1, dfn[v]);
}
int sumpath(int u, int v)
{
    int ret = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ret += querysum(rt, 1, n, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    if (u != v)
        ret += querysum(rt, 1, n, dfn[u] + 1, dfn[v]);
    return ret;
}
int maxpath(int u, int v)
{
    int ret = ~0x3f3f3f3f;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ret = max(ret, querymax(rt, 1, n, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    if (u != v)
        ret = max(ret, querymax(rt, 1, n, dfn[u] + 1, dfn[v]));
    return ret;
}
int minpath(int u, int v)
{
    int ret = 0x3f3f3f3f;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ret = min(ret, querymin(rt, 1, n, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    if (u != v)
        ret = min(ret, querymin(rt, 1, n, dfn[u] + 1, dfn[v]));
    return ret;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, u += 1, v += 1,
            tr[u].emplace_back(v, w, i), tr[v].emplace_back(u, w, i);

    dfs1(1, 0), dfs2(1, 1);
    build(rt, 1, n);

    cin >> m;
    char op[5];
    for (int u, v; m--;)
    {
        cin >> op >> u >> v;
        switch (op[0])
        {
        case 'C':
            updver(u, v);
            break;
        case 'N':
            opposite(++u, ++v);
            break;
        case 'S':
            cout << sumpath(++u, ++v) << '\n';
            break;
        case 'M':
            if (op[1] == 'A')
                cout << maxpath(++u, ++v) << '\n';
            else
                cout << minpath(++u, ++v) << '\n';
            break;
        }
    }
    return 0;
}