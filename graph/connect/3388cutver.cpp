#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e4 + 5, M = 1e5 + 5;
int n, m;
vector<int> g[N];

int rt, tim, dfn[N], low[N];
int cnt, cut[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++tim;
    int son = 0;
    for (int v : g[u])
        if (!dfn[v])
        {
            son++, tarjan(v), low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u] && u != rt)
                cnt += !cut[u], cut[u] = 1;
        }
        else
            low[u] = min(low[u], dfn[v]);
    if (son >= 2 && u == rt)
        cnt += !cut[u], cut[u] = 1;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v,
            g[u].emplace_back(v), g[v].emplace_back(u);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            rt = i, tarjan(i);
    cout << cnt << '\n';
    for (int i = 1; i <= n; i++)
        if (cut[i])
            cout << i << ' ';
    return 0;
}