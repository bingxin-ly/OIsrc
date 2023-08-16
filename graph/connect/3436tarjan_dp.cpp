#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 5, INF = 36501;
int n, m, f[N], rng[N];
vector<int> g[N], h[N];

int tim, dfn[N], low[N], cnt, col[N];
int top, stk[N], vis[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++tim, stk[++top] = u, vis[u] = 1;
    for (int v : g[u])
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    if (low[u] == dfn[u])
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
    cin >> n >> m, n += 1;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int u = 1; u <= n; u++)
        for (int v : g[u])
            if (col[u] == col[v])
                rng[col[u]] = 1;
            else
                h[col[v]].emplace_back(col[u]);
    f[col[n]] = 1;
    for (int u = 1; u <= cnt; u++)
    {
        if (f[u] && rng[u])
            f[u] = INF;
        for (int v : h[u])
            f[v] = min(f[v] + f[u], INF);
    }
    int mxn = 0;
    vector<int> ans;
    for (int i = 1; i < n; i++)
    {
        if (mxn < f[col[i]])
            mxn = f[col[i]], ans.clear();
        if (mxn == f[col[i]])
            ans.emplace_back(i);
    }
    if (mxn == INF)
        cout << "zawsze\n";
    else
        cout << mxn << '\n';
    cout << ans.size() << '\n';
    for (int i : ans)
        cout << i << ' ';
    return 0;
}