#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e3 + 5;
int n, m, deg[N];
vector<pair<int, int>> g[N];

int tim, dfn[N], low[N];
int top, stk[N], cnt, col[N];
void form(int u, int p = 0)
{
    cnt++;
    while (p != u)
        col[p = stk[top--]] = cnt;
}
void tarjan(int u, int i)
{
    dfn[u] = low[u] = ++tim, stk[++top] = u;
    for (const auto &[v, j] : g[u])
    {
        if (j == i)
            continue;
        if (!dfn[v])
        {
            tarjan(v, j), low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                form(v);
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v,
            g[u].emplace_back(v, i), g[v].emplace_back(u, i);
    tarjan(1, 0), form(1);
    for (int u = 1; u <= n; u++)
        for (const auto &[v, _] : g[u])
            if (u < v && col[u] != col[v])
                deg[col[u]]++, deg[col[v]]++;
    int leaves = 0;
    for (int i = 1; i <= cnt; i++)
        leaves += deg[i] == 1;
    cout << (++leaves >> 1);
    return 0;
}