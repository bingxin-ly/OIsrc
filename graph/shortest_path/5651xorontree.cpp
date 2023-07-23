#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, q, dis[N];
vector<pair<int, int>> g[N];

bool vis[N];
void bfs()
{
    queue<int> q;
    q.emplace(1), vis[1] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (const auto &[v, w] : g[u])
            if (!vis[v])
                dis[v] = dis[u] ^ w, q.emplace(v), vis[v] = true;
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    bfs();
    for (int u, v; q--;)
        cin >> u >> v, cout << (dis[u] ^ dis[v]) << '\n';
    return 0;
}