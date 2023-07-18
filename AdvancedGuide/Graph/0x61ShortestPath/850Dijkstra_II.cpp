// 迪杰斯特拉老爷子留给后人的宝贵遗产
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1.5e5 + 5;
int n, m;
vector<pair<int, int>> g[N];

int dis[N], vis[N]; // 记录到某个节点的最短路长度和访问标记
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
void dijkstra(int s)
{
    memset(dis, 0x7f, sizeof(dis)), memset(vis, 0, sizeof(vis));
    dis[s] = 0, q.emplace(0, s); // 初始化清空，将 s 作为初始节点入堆

    while (!q.empty())
    {
        int u = q.top().second; // 堆顶，未松弛节点的最小值
        q.pop();
        if (vis[u]) // 堆的懒惰删除
            continue;
        vis[u] = true;

        for (const auto &[v, w] : g[u])
            if (dis[v] > dis[u] + w)
                dis[v] = dis[u] + w, q.emplace(dis[v], v);
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w);
    dijkstra(1);
    cout << (dis[n] != 0x7f7f7f7f ? dis[n] : -1);
    return 0;
}