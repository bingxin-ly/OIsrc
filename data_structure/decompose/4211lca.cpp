#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e4 + 5, MOD = 201314;
int n, m;
vector<int> g[N];

int par[N], dep[N], siz[N], son[N];
void dfs1(int u)
{
    dep[u] = dep[par[u]] + 1, siz[u] = 1;
    for (int v : g[u])
    {
        dfs1(v);
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
    dfs2(son[u], u);
    for (int v : g[u])
        if (v != son[u])
            dfs2(v, v);
}

#define ls (p << 1)
#define rs (p << 1 | 1)
struct
{
    int val, tag;
} t[N << 2];
void pushup(int p) { t[p].val = (t[ls].val + t[rs].val) % MOD; }
void pushdown(int p, int l, int r)
{
    if (t[p].tag)
    {
        int mid = (l + r) >> 1, llen = mid - l + 1, rlen = r - mid;
        (t[ls].val += 1ll * t[p].tag * llen % MOD) %= MOD;
        (t[rs].val += 1ll * t[p].tag * rlen % MOD) %= MOD;
        t[ls].tag += t[p].tag, t[rs].tag += t[p].tag, t[p].tag = 0;
    }
}
void update(int p, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return (t[p].val += r - l + 1) %= MOD, t[p].tag += 1, void();
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (x <= mid)
        update(ls, l, mid, x, y);
    if (y > mid)
        update(rs, mid + 1, r, x, y);
    pushup(p);
}
int query(int p, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return t[p].val;
    pushdown(p, l, r);
    int mid = (l + r) >> 1, ret = 0;
    if (x <= mid)
        ret = query(ls, l, mid, x, y);
    if (y > mid)
        (ret += query(rs, mid + 1, r, x, y)) %= MOD;
    return ret;
}

int ask[N], ans[N];
vector<int> lf[N], rh[N];
void update(int u)
{
    while (u)
        update(1, 1, n, dfn[top[u]], dfn[u]), u = par[top[u]];
}
int query(int u)
{
    int ret = 0;
    while (u)
        (ret += query(1, 1, n, dfn[top[u]], dfn[u])) %= MOD, u = par[top[u]];
    return ret;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 2; i <= n; i++)
        cin >> par[i], g[++par[i]].emplace_back(i);
    dfs1(1), dfs2(1, 1);
    for (int i = 1, l, r; i <= m; i++)
    {
        cin >> l >> r >> ask[i], ++ask[i];
        lf[l].emplace_back(i), rh[r + 1].emplace_back(i);
    }

    for (int i = 1; i <= n; i++)
    {
        update(i);
        for (int j : rh[i])
            (ans[j] += query(ask[j])) %= MOD;
        for (int j : lf[i])
            (ans[j] -= query(ask[j])) %= MOD;
    }
    for (int i = 1; i <= m; i++)
        cout << (ans[i] % MOD + MOD) % MOD << '\n';
    return 0;
}