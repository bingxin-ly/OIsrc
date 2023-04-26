#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e4 + 10, M = 1e5 + 10;

int n, m, k, s, t, ks[20];
struct edge
{
    int to, w;
};
vector<edge> graph[N];

inline void add(int u, int v, int w)
{
    graph[u].push_back({v, w});
}

int dist[N];
bool st[N];

typedef pair<int, int> PII;
void dijkstra(int start)
{
    // memset(dist, 0x7f, sizeof(dist));
    for (int i = 1; i <= n; i++)
        dist[i] = LLONG_MAX;
    memset(st, false, sizeof(st));
    dist[start] = 0;

    priority_queue<PII, vector<PII>, greater<>> heap;
    heap.push({0, start});

    while (!heap.empty())
    {
        auto t = heap.top();
        heap.pop();
        int distance = t.first, ver = t.second;

        if (st[ver])
            continue;
        st[ver] = true;

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

int ans = LLONG_MAX, DIST[20][20];
bool vis[N];
void dfs(int u, int sum, int cur)
{
    if (cur == k)
        ans = min(ans, sum + DIST[u][k + 1]);

    for (int i = 1; i <= k; i++)
    {
        if (vis[i])
            continue;
        vis[i] = 1;
        dfs(i, sum + DIST[u][i], cur + 1);
        vis[i] = 0;
    }
}
signed main()
{
    cin >> n >> m >> k >> s >> t;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, add(u, v, w);
    for (int i = 1; i <= k; i++)
        cin >> ks[i];
    ks[0] = s, ks[k + 1] = t;

    for (int i = 0; i <= k + 1; i++)
    {
        dijkstra(ks[i]);
        for (int j = 0; j <= k + 1; j++)
            DIST[i][j] = dist[ks[j]];
    }

    dfs(0, 0, 0);
    cout << (ans == LLONG_MAX ? -1 : ans) << endl;
    return 0;
}
