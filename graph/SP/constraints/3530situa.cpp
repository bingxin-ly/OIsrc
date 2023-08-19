#include <bits/stdc++.h>
using namespace std;

constexpr int N = 605;
int n, m1, m2, ans, w[N][N];
vector<pair<int, int>> g[N];

int tim, dfn[N], low[N], top, stk[N], vis[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++tim, stk[++top] = u, vis[u] = 1;
    for (const auto &[v, w] : g[u])
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    if (low[u] == dfn[u])
    {
        vector<int> scc;
        for (int p = 0; p != u;)
            scc.emplace_back(p = stk[top--]), vis[p] = 0;
        for (int k : scc)
            for (int i : scc)
                for (int j : scc)
                    w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
        for (int i : scc)
            if (w[i][i] < 0)
                cout << "NIE", exit(0);
        int mxn = 0;
        for (int u : scc)
            for (int v : scc)
                mxn = max(mxn, w[u][v]);
        ans += mxn + 1;
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m1 >> m2;
    memset(w, 0x3f, sizeof(w));
    for (int i = 1; i <= n; i++)
        w[i][i] = 0;
    for (int i = 1, u, v; i <= m1; i++)
        cin >> u >> v,
            g[u].emplace_back(v, 1), g[v].emplace_back(u, -1),
            w[u][v] = min(w[u][v], 1), w[v][u] = min(w[v][u], -1);
    for (int i = 1, u, v; i <= m2; i++)
        cin >> u >> v,
            g[u].emplace_back(v, 0), w[v][u] = min(w[v][u], 0);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    cout << ans;
    return 0;
}