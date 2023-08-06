#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int N = 2e4 + 5, W = 105;
int n, m, s, t, ans = 1 << 30;
vector<pii> g[N];

int dis[W][N], vis[W][N];
priority_queue<pii, vector<pii>, greater<>> q;
void dijkstra()
{
    memset(dis, 0x3f, sizeof(dis)), dis[1][t] = 0;
    q.emplace(1, t);

    while (!q.empty())
    {
        auto [i, u] = q.top();
        q.pop();
        if (vis[i][u])
            continue;
        vis[i][u] = 1;
        if (i > 100)
        {
            ans = min(ans, dis[i][u]);
            continue;
        }

        for (const auto &[v, w] : g[u])
            if (dis[i + 1][v] > dis[i][u] + w / i)
                dis[i + 1][v] = dis[i][u] + w / i, q.emplace(i + 1, v);
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> s >> t;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w,
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    dijkstra();
    for (int i = 1; i <= 101; i++)
        ans = min(ans, dis[i][s]);
    cout << ans;
    return 0;
}