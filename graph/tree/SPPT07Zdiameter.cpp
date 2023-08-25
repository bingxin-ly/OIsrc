#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 5;
int n;
vector<int> g[N];

int ans, dep[N];
void dp(int u, int p)
{
    for (int v : g[u])
        if (v != p)
        {
            dp(v, u);
            ans = max(ans, dep[u] + dep[v] + 1);
            dep[u] = max(dep[u], dep[v] + 1);
        }
}

int s;
void dfs(int u, int p)
{
    dep[u] = dep[p] + 1;
    if (dep[u] > dep[s])
        s = u;
    for (int v : g[u])
        if (v != p)
            dfs(v, u);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    dfs(1, 0), dfs(s, 0);
    cout << dep[s] - 1;
    return 0;
}