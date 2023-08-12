#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 5, M = 5e4 + 5;
int n, m, q;
vector<pair<int, int>> g[N];
struct edge
{
    int u, v, w;
    bool operator<(const edge &o) const { return w > o.w; }
} e[M];

int fa[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int dep[N], anc[N][15], mnv[N][15];
void pretask(int u, int p)
{
    dep[u] = dep[p] + 1, anc[u][0] = p;
    for (const auto &[v, w] : g[u])
        if (v != p)
            pretask(v, u), mnv[v][0] = w;
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

    sort(e + 1, e + m + 1);
    iota(fa + 1, fa + n + 1, 1);
    for (int i = 1, x, y; i <= m; i++)
    {
        x = find(e[i].u), y = find(e[i].v);
        if (x == y)
            continue;
        fa[x] = y;
        g[e[i].u].emplace_back(e[i].v, e[i].w);
        g[e[i].v].emplace_back(e[i].u, e[i].w);
    }
    for (int i = 1; i <= n; i++)
        if (!dep[i])
            pretask(i, 0);

    for (int k = 1; k <= __lg(n); k++)
        for (int u = 1; u <= n; u++)
            anc[u][k] = anc[anc[u][k - 1]][k - 1],
            mnv[u][k] = min(mnv[u][k - 1], mnv[anc[u][k - 1]][k - 1]);
    cin >> q;
    for (int u, v; q--;)
    {
        int ans = 1 << 30;
        cin >> u >> v;
        if (dep[u] < dep[v])
            swap(u, v);
        for (int k = __lg(dep[u]); k >= 0; k--)
            if (dep[anc[u][k]] >= dep[v])
                ans = min(ans, mnv[u][k]), u = anc[u][k];
        if (u != v)
        {
            for (int k = __lg(dep[u]); k >= 0; k--)
                if (anc[u][k] != anc[v][k])
                    ans = min(ans, min(mnv[u][k], mnv[v][k])),
                    u = anc[u][k], v = anc[v][k];
            ans = min(ans, min(mnv[u][0], mnv[v][0]));
            u = anc[u][0], v = anc[v][0];
        }
        cout << (u ? ans : -1) << '\n';
    }
    return 0;
}