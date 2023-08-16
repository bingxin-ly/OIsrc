#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m;
long long ans[N], siz[N];
vector<int> g[N];

int tim, dfn[N], low[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++tim;
    long long r = n - 1;
    ans[u] = r, siz[u] = 1;
    for (int v : g[u])
        if (!dfn[v])
        {
            tarjan(v), low[u] = min(low[u], low[v]), siz[u] += siz[v];
            if (low[v] >= dfn[u])
                ans[u] += siz[v] * (n - siz[v]), r -= siz[v];
        }
        else
            low[u] = min(low[u], dfn[v]);
    ans[u] += r * (n - r);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v,
            g[u].emplace_back(v), g[v].emplace_back(u);
    tarjan(1);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
    return 0;
}