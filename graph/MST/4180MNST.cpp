#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5, M = 3e5 + 5;
int n, m;
vector<pair<int, int>> g[N];
struct edge
{
    int u, v, w;
    bool operator<(const edge &o) const { return w < o.w; }
} e[M];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int vis[M], dep[N], anc[N][18];
struct dat
{
    int max, sec;
    dat() { max = sec = ~(1 << 30); }
} val[N][18];
void upd(dat &v, int x)
{
    if (x > v.max)
        swap(x, v.max);
    if (v.max > x && x > v.sec)
        swap(x, v.sec);
}
dat upd(dat x, dat y) { return upd(x, y.max), upd(x, y.sec), x; }
void pretask(int u, int p)
{
    dep[u] = dep[p] + 1, anc[u][0] = p;
    for (const auto &[v, w] : g[u])
        if (v != p)
            upd(val[v][0], w), pretask(v, u);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("D:\\Workspace\\.in", "r", stdin);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e + 1, e + m + 1), iota(fa + 1, fa + n + 1, 1);
    long long sum = 0;
    for (int i = 1, x, y; i <= m; i++)
    {
        x = find(e[i].u), y = find(e[i].v);
        if (x == y)
            continue;
        fa[x] = y, vis[i] = 1, sum += e[i].w;
        g[e[i].u].emplace_back(e[i].v, e[i].w);
        g[e[i].v].emplace_back(e[i].u, e[i].w);
    }

    pretask(1, 0);
    for (int k = 1; k <= __lg(n); k++)
        for (int u = 1; u <= n; u++)
            anc[u][k] = anc[anc[u][k - 1]][k - 1],
            val[u][k] = upd(val[u][k - 1], val[anc[u][k - 1]][k - 1]);
    int dlt = 1 << 30;
    for (int i = 1; i <= m; i++)
    {
        if (vis[i])
            continue;
        int u = e[i].u, v = e[i].v;
        if (dep[u] < dep[v])
            swap(u, v);
        dat res;
        for (int k = __lg(dep[u]); k >= 0; k--)
            if (dep[anc[u][k]] >= dep[v])
                res = upd(res, val[u][k]), u = anc[u][k];
        for (int k = __lg(dep[u]); k >= 0; k--)
            if (anc[u][k] != anc[v][k])
                res = upd(res, upd(val[u][k], val[v][k])),
                u = anc[u][k], v = anc[v][k];
        if (u != v)
            res = upd(res, upd(val[u][0], val[v][0]));
        dlt = min(dlt, e[i].w - (e[i].w > res.max ? res.max : res.sec));
    }
    cout << sum + dlt;
    return 0;
}