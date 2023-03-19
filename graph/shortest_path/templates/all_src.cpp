#include <bits/stdc++.h>
using namespace std;

const ssize_t INF = 1e9; // 虽然1e9没有溢出，但运算中极易出问题！
/* const double INF = 1e9
   #define INF 1e9 也都可以
*/
const int MAXN = 3e3 + 10, MAXM = 6e3 + 10;

struct edge
{
    int to, w;
};
vector<edge> graph[MAXN];
int n, m;
int cnt[MAXN];      // cnt[x]存储 1到 x的最短路中经过的点数
ssize_t dist[MAXN], // dist[x]存储 1号点到 x的最短距离
    h[MAXN];        // 势能数组
bool vis[MAXN];     // 存储每个点是否在队列中


inline void add(int u, int v, int w = 1)
{
    graph[u].push_back({v, w});
}

// 如果存在负环，则返回true，否则返回false。
bool spfa(int s)
{
    // 不需要初始化dist数组
    // 原理：如果某条最短路径上有n个点（除了自己），那么加上自己之后一共有n+1个点，由抽屉原理一定有两个点相同，所以存在环。

    queue<int> q;
    memset(h, 0x3f, sizeof(h));
    h[s] = 0, vis[s] = true;
    q.push(s);
    for (int i = 1; i <= n; i++)
    {
        q.push(i);
        vis[i] = true;
    }

    while (q.size())
    {
        int u = q.front();
        q.pop();

        vis[u] = false;

        for (auto i : graph[u])
        {
            int j = i.to;
            if (h[j] > h[u] + i.w)
            {
                h[j] = h[u] + i.w;
                cnt[j] = cnt[u] + 1;
                if (cnt[j] >= n + 1)
                    return true;
                /* 如果从1号点到x的最短路中包含至少n个点
                （不包括自己），则说明存在环*/

                if (!vis[j])
                {
                    q.push(j);
                    vis[j] = true;
                }
            }
        }
    }

    return false;
}
typedef pair<int, int> PII;

// 求1号点到n号点的最短距离，如果不存在，则返回-1
void dijkstra(int s)
{
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    memset(vis, false, sizeof vis);
    dist[s] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, s}); // first存储距离，second存储节点编号

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;

        if (vis[ver])
            continue;
        vis[ver] = true;

        for (auto i : graph[ver])
        {
            int j = i.to;
            if (dist[j] > distance + i.w)
            {
                dist[j] = distance + i.w;
                heap.push({dist[j], j});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    // memset(f, 0x3f, sizeof(f));
    // for (int i = 1; i <= n; i++)
    //     f[i][i] = 0;
    for (int i = 1, u, v, w; i <= m; i++)
    {
        cin >> u >> v >> w;
        add(u, v, w);
    }
    for (int i = 1; i <= n; i++)
        add(0, i, 0);

    if (spfa(0))
    {
        cout << -1 << endl;
        return 0;
    }
    for (int u = 1; u <= n; u++)
        for (auto &i : graph[u])
            i.w += h[u] - h[i.to];
    for (int i = 1; i <= n; i++)
    {
        dijkstra(i);
        ssize_t ans = 0;

        for (int j = 1; j <= n; j++)
        {
            if (dist[j] == INF)
                ans += j * INF;
            else
                ans += j * (dist[j] + h[j] - h[i]);
        }
        cout << ans << endl;
    }
    return 0;
}
