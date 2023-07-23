/* 一些启示：可以看看dijkstra的初始化部分
   这样会慢很多是真的（真的慢很多），但是在这里就用上了
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2.5e4 + 5;
int n, r, p, s;
vector<tuple<int, int, bool>> g[N];

int cnt, col[N], deg[N];
vector<int> blo[N];
void color(int u)
{
    col[u] = cnt;
    blo[cnt].emplace_back(u);
    for (const auto &[v, w, t] : g[u])
        if (t && !col[v])
            color(v);
}

int dis[N];
bool vis[N];
queue<int> q;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> heap;
void dijkstra(int k)
{
    for (int u : blo[k])
        heap.emplace(dis[u], u);
    while (!heap.empty())
    {
        int u = heap.top().second;
        heap.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (const auto &[v, w, t] : g[u])
            if (t)
            {
                if (dis[v] > dis[u] + w)
                    dis[v] = dis[u] + w, heap.emplace(dis[v], v);
            }
            else
            {
                dis[v] = min(dis[v], dis[u] + w);
                if (!--deg[col[v]])
                    q.emplace(col[v]);
            }
    }
}
void topo()
{
    for (int i = 1; i <= cnt; i++)
        if (!deg[i])
            q.emplace(i);
    memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        dijkstra(k);
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> r >> p >> s; // rp++
    for (int i = 1, u, v, w; i <= r; i++)
        cin >> u >> v >> w,
            g[u].emplace_back(v, w, true), g[v].emplace_back(u, w, true);
    for (int i = 1, u, v, w; i <= p; i++)
        cin >> u >> v >> w,
            g[u].emplace_back(v, w, false);

    for (int u = 1; u <= n; u++)
        if (!col[u])
            cnt += 1, color(u);
    for (int u = 1; u <= n; u++)
        for (const auto &[v, w, t] : g[u])
            if (!t)
                deg[col[v]] += 1;

    topo();
    for (int i = 1; i <= n; i++)
        dis[i] > 10000 * n ? cout << "NO PATH\n" : cout << dis[i] << '\n';
    return 0;
}