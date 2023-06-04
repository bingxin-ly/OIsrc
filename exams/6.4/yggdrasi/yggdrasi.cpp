#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 7e5 + 10;
int n, p[N];
vector<pair<int, int>> tr[N];

int f[N], sz[N];
void dfs1(int u, int fa)
{
    sz[u] = 1;
    for (auto i : tr[u])
    {
        int v = i.first;
        if (v == fa)
            continue;
        dfs1(v, u);
        f[u] += f[v] + (i.second - p[u]) * sz[v];
        sz[u] += sz[v];
    }
}
int g[N], rt, ans;
void dfs2(int u, int fa)
{
    if (g[u] < ans) // 第一个点绝对等于，导致无法更新
        ans = g[u], rt = u;
    else if (g[u] == ans)
        rt = min(rt, u);
    for (auto i : tr[u])
    {
        auto v = i.first;
        if (v == fa)
            continue;
        g[v] = g[u] - (i.second - p[u]) * sz[v] + (i.second - p[v]) * (n - sz[v]);
        dfs2(v, u);
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w,
            tr[u].emplace_back(v, w), tr[v].emplace_back(u, w);

    dfs1(1, 0);
    rt = 1, ans = g[1] = f[1];
    dfs2(1, 0);

    cout << rt << '\n'
         << ans;
    return 0;
}