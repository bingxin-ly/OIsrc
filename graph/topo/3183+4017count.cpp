#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5, MOD = 80112002;
int n, m, ans, in[N], f[N];
vector<int> g[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v), in[v] += 1;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i] && !g[i].empty())
            q.emplace(i), f[i] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (g[u].empty())
            (ans += f[u]) %= MOD;
        for (int v : g[u])
        {
            (f[v] += f[u]) %= MOD;
            if (!--in[v])
                q.emplace(v);
        }
    }
    cout << ans;
    return 0;
}