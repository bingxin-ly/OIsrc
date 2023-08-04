#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr long long INF = 1e9;
constexpr int N = 3e3 + 10, M = 6e3 + 10;

vector<pii> g[N];
int n, m;
int cnt[N];             // cnt[x] 存储 1 到 x 的最短路中经过的点数
long long dis[N], h[N]; // h[x] 为势能数组
bool vis[N];            // 记录每个点是否在队列中

// 如果存在负环，则返回 true，否则返回 false
bool spfa(int s)
{
    // 不需要初始化dist数组
    // 原理：如果某条最短路径上有n个点（除了自己），那么加上自己之后一共有n+1个点，由抽屉原理一定有两个点相同，所以存在环。
    queue<int> q;
    memset(h, 0x3f, sizeof(h));
    h[s] = 0, vis[s] = true;
    q.emplace(s);
    for (int i = 1; i <= n; i++)
        q.emplace(i), vis[i] = true;

    while (q.size())
    {
        int u = q.front();
        q.pop();

        vis[u] = false;

        for (const auto &[v, w] : g[u])
        {
            if (h[v] > h[u] + w)
            {
                h[v] = h[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n + 1)
                    return true;
                /* 如果从1号点到x的最短路中包含至少n个点
                （不包括自己），则说明存在环*/

                if (!vis[v])
                    q.emplace(v), vis[v] = true;
            }
        }
    }

    return false;
}

void dijkstra(int s)
{
    memset(vis, false, sizeof vis);
    fill(dis + 1, dis + n + 1, INF), dis[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> heap;
    heap.emplace(0, s); // first存储距离，second存储节点编号

    while (heap.size())
    {
        int u = heap.top().second;
        heap.pop();
        if (vis[u])
            continue;
        vis[u] = true;

        for (const auto &[v, w] : g[u])
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                heap.emplace(dis[v], v);
            }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w);
    for (int i = 1; i <= n; i++)
        g[0].emplace_back(i, 0);

    if (spfa(0))
    {
        cout << -1 << endl;
        return 0;
    }
    for (int u = 1; u <= n; u++)
        for (auto &[v, w] : g[u])
            w += h[u] - h[v];
    for (int i = 1; i <= n; i++)
    {
        dijkstra(i);
        long long ans = 0;

        for (int j = 1; j <= n; j++)
        {
            if (dis[j] == INF)
                ans += j * INF;
            else
                ans += j * (dis[j] + h[j] - h[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}