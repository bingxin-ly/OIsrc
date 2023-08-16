#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 5;
int n, m;
vector<pair<int, int>> g[N];
vector<vector<int>> ans;

int tim, dfn[N], low[N];
int top, stk[N];
void form(int u, int p = 0)
{
    vector<int> CC;
    while (p != u)
        CC.emplace_back(p = stk[top--]);
    ans.emplace_back(CC);
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
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i, 0), form(i);
    cout << ans.size() << '\n';
    for (auto CC : ans)
    {
        cout << CC.size() << '\n';
        for (int ver : CC)
            cout << ver << ' ';
        cout << '\n';
    }
    return 0;
}