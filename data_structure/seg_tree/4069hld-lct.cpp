#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
vector<pair<int, int>> g[N];
long long dis[N], val[N];

namespace hld
{
    int fa[N], dep[N], siz[N], son[N];
    void dfs1(int u, int p)
    {
        siz[u] = 1, fa[u] = p,
        dep[u] = dep[p] + 1, val[dep[u]] = dis[u];
        for (const auto &[v, w] : g[u])
            if (v != p)
            {
                dis[v] = dis[u] + w;
                dfs1(v, u);
                siz[v] += siz[u];
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
namespace lct
{
    struct line
    {
        int k, b;
    } lis[N];
    int t[N << 2], cnt;

#define ls (p << 1)
#define rs (p << 1 | 1)
    void spread(int p, int l, int r, int g)
    {
        int &f = t[p],
            mid = (l + r) >> 1;
    }
    void update(int p, int l, int r, int ql, int qr, int idx)
    {
        if (ql <= l && r <= qr)
            return spread(p, l, r, idx);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(ls, l, mid, ql, qr, idx);
        if (qr > mid)
            update(rs, mid + 1, r, ql, qr, idx);
    }
}
using namespace hld;
using namespace lct;

void insert(int u, int v, int k, int b)
{
    while (top[u] != top[v])
}
int query(int u, int v)
{
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w,
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    dfs1(1, 0), dfs2(1, 1);
    for (int op, s, t, a, b, ca; m--;)
    {
        cin >> op >> s >> t;
        if (op == 1)
            cin >> a >> b,
                ca = lca(s, t),
                insert(s, ca, -a, a * dis[s] + b),
                insert(ca, t, a, a * dis[s] - 2 * a * dis[ca] + b);
        else
            cout << query(s, t) << '\n';
    }
    return 0;
}