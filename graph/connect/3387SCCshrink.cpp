#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 5;
int n, m, poi[N], val[N], f[N];
vector<int> o[N], p[N];

int tim, dfn[N], low[N], cnt, col[N];
int top, stk[N], vis[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++tim, stk[++top] = u, vis[u] = 1;
    for (int v : o[u])
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    if (dfn[u] == low[u])
    {
        col[u] = ++cnt;
        while (stk[top] != u)
            col[stk[top]] = cnt, vis[stk[top--]] = 0;
        vis[stk[top--]] = 0;
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> poi[i];
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, o[u].emplace_back(v);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int u = 1; u <= n; u++)
    {
        val[col[u]] += poi[u];
        for (int v : o[u])
            if (col[u] != col[v])
                p[col[u]].emplace_back(col[v]);
    }
    int ans = 0;
    for (int u = cnt; u; u--)
    {
        f[u] += val[u], ans = max(ans, f[u]);
        for (int v : p[u])
            f[v] = max(f[v], f[u]);
    }
    cout << ans;
    return 0;
}