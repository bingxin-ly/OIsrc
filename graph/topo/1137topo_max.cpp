#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, in[N], ds[N];
vector<int> g[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v), in[v] += 1;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i])
            q.emplace(i), ds[i] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : g[u])
        {
            ds[v] = max(ds[v], ds[u] + 1);
            if (!--in[v])
                q.emplace(v);
        }
    }
    for (int i = 1; i <= n; i++)
        cout << ds[i] << '\n';
    return 0;
}