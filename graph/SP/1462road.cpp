// 二分 + 最短路
// 第一次写假了，看来还是要多测几组，最好有暴力对拍
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int N = 1e4 + 5;
int n, m, b, f[N];
vector<pii> g[N];

int dis[N], vis[N];
bool dijkstra(int x)
{
    if (f[1] > x)
        return false; // 起点还要花钱，你怎么不去抢啊
    memset(vis, 0, sizeof(vis)), memset(dis, 0x3f, sizeof(dis)), dis[1] = 0;
    priority_queue<pii, vector<pii>, greater<>> q;
    q.emplace(0, 1);
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (const auto &[v, w] : g[u])
            if (f[v] <= x && dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                q.emplace(dis[v], v);
            }
    }
    return dis[n] <= b;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> b;
    for (int i = 1; i <= n; i++)
        cin >> f[i];
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w,
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    int l = 0, r = 1e9 + 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (dijkstra(mid))
            r = mid;
        else
            l = mid + 1;
    }
    if (l != 1e9 + 1)
        cout << l;
    else
        cout << "AFK";
    return 0;
}