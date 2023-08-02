#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
constexpr long long INF = 123456789123456789ll;
int n, m;
vector<pair<int, int>> g[N];
long long dis[N];

namespace hld
{
    int fa[N], dep[N], siz[N], son[N];
    void dfs1(int u, int p)
    {
        siz[u] = 1, fa[u] = p, dep[u] = dep[p] + 1;
        for (const auto &[v, w] : g[u])
            if (v != p)
            {
                dis[v] = dis[u] + w;
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
        for (const auto &[v, w] : g[u])
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
}
using namespace hld;
namespace lct
{
    struct line
    {
        int k;
        long long b;
    };
    inline long long calc(line l, long long x) { return l.k * x + l.b; }

    struct tree
    {
        line seg;
        long long val;
        tree() { seg.k = 0, seg.b = val = 123456789123456789ll; }
    } t[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
    inline void pushup(int p, int l, int r)
    {
        t[p].val = min(
            t[p].val,
            min(calc(t[p].seg, dis[rnk[l]]),
                calc(t[p].seg, dis[rnk[r]])));
        t[p].val = min(t[p].val, min(t[ls].val, t[rs].val));
    }
    void spread(int p, int l, int r, line ln)
    {
        int mid = (l + r) >> 1;
        if (calc(ln, dis[rnk[mid]]) < calc(t[p].seg, dis[rnk[mid]]))
            swap(t[p].seg, ln);
        if (calc(ln, dis[rnk[l]]) < calc(t[p].seg, dis[rnk[l]]))
            spread(ls, l, mid, ln);
        if (calc(ln, dis[rnk[r]]) < calc(t[p].seg, dis[rnk[r]]))
            spread(rs, mid + 1, r, ln);
        pushup(p, l, r);
    }
    void update(int p, int l, int r, int ql, int qr, line ln)
    {
        int mid = (l + r) >> 1;
        if (ql <= l && r <= qr)
            return spread(p, l, r, ln);
        if (ql <= mid)
            update(ls, l, mid, ql, qr, ln);
        if (qr > mid)
            update(rs, mid + 1, r, ql, qr, ln);
        pushup(p, l, r);
    }
    long long askmin(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return t[p].val;
        int mid = (l + r) >> 1;
        long long ret = min(
            calc(t[p].seg, dis[rnk[max(l, ql)]]),
            calc(t[p].seg, dis[rnk[min(r, qr)]]));
        if (ql <= mid)
            ret = min(ret, askmin(ls, l, mid, ql, qr));
        if (qr > mid)
            ret = min(ret, askmin(rs, mid + 1, r, ql, qr));
        return ret;
    }
}
using namespace lct;

void insert(int u, int v, int k, long long b)
{
    line ln{k, b};
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        update(1, 1, n, dfn[top[u]], dfn[u], ln);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    update(1, 1, n, dfn[u], dfn[v], ln);
}
long long query(int u, int v, long long res = 123456789123456789ll)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        res = min(res, askmin(1, 1, n, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    res = min(res, askmin(1, 1, n, dfn[u], dfn[v]));
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w,
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    dfs1(1, 0), dfs2(1, 1);
    for (int op, s, t, a, b, ca; m--;)
    {
        cin >> op >> s >> t;
        if (op == 1)
        {
            cin >> a >> b, ca = lca(s, t);
            insert(s, ca, -a, a * dis[s] + b),
                insert(ca, t, a, a * dis[s] - 2 * a * dis[ca] + b);
        }
        else
            cout << query(s, t) << '\n';
    }
    return 0;
}