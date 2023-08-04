#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 5, MOD = 1e5 + 3;
int n, m, d[N], c[N], v[N];
vector<int> g[N];

void bfs()
{
    queue<int> q;
    q.emplace(1);
    memset(d, 0x3f, sizeof(d)), d[1] = 0, c[1] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (v[u])
            continue;
        v[u] = true;
        for (int v : g[u])
        {
            if (d[v] > d[u] + 1)
                d[v] = d[u] + 1, c[v] = c[u];
            else if (d[v] == d[u] + 1)
                (c[v] += c[u]) %= MOD;
            q.emplace(v);
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    bfs();
    for (int i = 1; i <= n; i++)
        cout << c[i] << '\n';
    return 0;
}