/* 二分 + 双端队列
   之前还没写过这样的 01 双端 BFS，看来还是欠太多了
*/
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
int n, m, k, dis[N];
vector<pair<int, int>> g[N];

deque<int> q;
bool bfs(int p)
{
    memset(dis, 0x3f, sizeof(dis));
    q.emplace_back(1), dis[1] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        for (const auto &[v, ww] : g[u])
        {
            int w = ww > p;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                w ? q.emplace_back(v) : q.emplace_front(v);
            }
        }
    }
    return dis[n] <= k;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    int l = 0, r = 1000001;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (bfs(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << (l != 1000001 ? l : -1);
    return 0;
}