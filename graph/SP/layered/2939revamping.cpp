#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 5e5 + 10, K = 2e1 + 1;

int cnt, nxt[M * K * 2], w[M * K * 2], e[M * K * 2], head[N * K];
void add(int u, int v, int cost)
{
    e[++cnt] = v;
    w[cnt] = cost;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

struct node
{
    int u, dis;
    bool operator<(const node x) const { return dis > x.dis; }
};

priority_queue<node> q;
int dist[N * K];

void dijkstra(int s)
{
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    q.push({s, 0});
    
    while (!q.empty())
    {
        node x = q.top();
        q.pop();
        int u = x.u, dis = x.dis;
        if (dis != dist[u]) // 省去了vis
            continue;
        for (int v = head[u]; v; v = nxt[v])
            if (dist[e[v]] > dist[u] + w[v])
            {
                dist[e[v]] = dist[u] + w[v];
                q.push({e[v], dist[e[v]]});
            }
    }
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1, u, v, cost; i <= m; i++)
    {
        cin >> u >> v >> cost;
        add(u, v, cost);
        add(v, u, cost);
        for (int j = 1; j <= k; j++)
        {
            add(n * j + u, n * j + v, cost);
            add(n * j + v, n * j + u, cost);
            add(n * (j - 1) + u, n * j + v, 0);
            add(n * (j - 1) + v, n * j + u, 0);
        }
    }

    dijkstra(1);

    int ans = dist[n];
    for (int i = 1; i <= k; i++)
        ans = min(ans, dist[i * n + n]);
    cout << ans;
    return 0;
}
