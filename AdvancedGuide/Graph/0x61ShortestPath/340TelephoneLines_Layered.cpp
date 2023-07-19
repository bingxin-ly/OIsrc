#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
int n, m, k;
vector<pair<int, int>> g[N];

int dis[N][N], vis[N][N];
void SPFA()
{
    queue<pair<int, int>> q;
    memset(dis, 0x3f, sizeof(dis));
    q.emplace(1, 0), vis[1][0] = true, dis[1][0] = 0;
    while (!q.empty())
    {
        auto [u, p] = q.front();
        q.pop(), vis[u][p] = false;
        for (const auto &[v, w] : g[u])
        {
            if (dis[v][p] > max(dis[u][p], w))
            {
                dis[v][p] = max(dis[u][p], w);
                if (!vis[v][p])
                    q.emplace(v, p), vis[v][p] = true;
            }
            if (p < k && dis[v][p + 1] > dis[u][p])
            {
                dis[v][p + 1] = dis[u][p];
                if (!vis[v][p + 1])
                    q.emplace(v, p + 1), vis[v][p + 1] = true;
            }
        }
    }
}
void dijkstra()
{
    using pdp = pair<int, pair<int, int>>;
    priority_queue<pdp, vector<pdp>, greater<>> q;
    memset(dis, 0x3f, sizeof(dis));
    q.emplace(0, make_pair(1, 0)), dis[1][0] = 0;
    while (!q.empty())
    {
        auto [u, p] = q.top().second;
        q.pop();
        if (vis[u][p])
            continue;
        vis[u][p] = true;
        for (const auto &[v, w] : g[u])
        {
            if (dis[v][p] > max(dis[u][p], w))
                dis[v][p] = max(dis[u][p], w), q.emplace(dis[v][p], make_pair(v, p));
            if (p < k && dis[v][p + 1] > dis[u][p])
                dis[v][p + 1] = dis[u][p], q.emplace(dis[v][p + 1], make_pair(v, p + 1));
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    // SPFA();
    dijkstra();
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= k; i++)
        ans = min(ans, dis[n][i]);
    cout << (ans != 0x3f3f3f3f ? ans : -1);
    return 0;
}