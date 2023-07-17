#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e3 + 5, MOD = 80112002;
int n, m, in[N], out[N];
int ans, f[N];
vector<int> g[N];

void topo()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i])
            f[i] = 1, q.emplace(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : g[u])
        {
            (f[v] += f[u]) %= MOD;
            if (!--in[v])
            {
                if (out[v])
                    q.emplace(v);
                else
                    (ans += f[v]) %= MOD;
            }
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, in[v] += 1, out[u] += 1, g[u].emplace_back(v);
    topo();
    cout << ans;
    return 0;
}