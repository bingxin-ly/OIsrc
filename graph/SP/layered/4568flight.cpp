#include <bits/stdc++.h>
using namespace std;
using piii = tuple<int, int, int>;

constexpr int N = 1e4 + 5;
int n, m, k, s, t;
vector<pair<int, int>> g[N];

int dis[11][N], vis[11][N];
priority_queue<piii, vector<piii>, greater<>> q;
void dijkstra()
{
    memset(dis, 0x3f, sizeof(dis)), dis[0][s] = 0;
    q.emplace(0, 0, s);
    while (!q.empty())
    {
        auto [_, i, u] = q.top();
        q.pop();
        if (vis[i][u])
            continue;
        vis[i][u] = 1;
        for (const auto &[v, w] : g[u])
        {
            if (dis[i][v] > dis[i][u] + w)
                dis[i][v] = dis[i][u] + w, q.emplace(dis[i][v], i, v);
            if (i < k && dis[i + 1][v] > dis[i][u])
                dis[i + 1][v] = dis[i][u], q.emplace(dis[i + 1][v], i + 1, v);
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k >> s >> t;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w,
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    dijkstra();
    int ans = 1 << 30;
    for (int i = 0; i <= k; i++)
        ans = min(ans, dis[i][t]);
    cout << ans;
    return 0;
}