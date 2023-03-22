#include <bits/stdc++.h>
using namespace std;

const int maxn = 100100;
const int maxm = 500500;

int nextt[maxm * 42], w[maxm * 42], to[maxm * 42], head[maxn * 42], cnt = 0;

void add(int u, int v, int cost)
{
    cnt++;
    nextt[cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
    w[cnt] = cost;
}

struct node
{
    int u, dis;
    bool operator<(const node x) const
    {
        return dis > x.dis;
    }
};

priority_queue<node> q;
int dist[maxn * 21];

void dij(int s)
{
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    q.push({s, 0});
    while (!q.empty())
    {
        node fr = q.top();
        q.pop();
        int u = fr.u, dis = fr.dis;
        if (dis != dist[u])
            continue;
        for (int v = head[u]; v; v = nextt[v])
            if (dist[to[v]] > dist[u] + w[v])
            {
                dist[to[v]] = dist[u] + w[v];
                q.push((node){to[v], dist[to[v]]});
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
    dij(1);
    int ans = dist[n];
    for (int i = 1; i <= k; i++)
        ans = min(ans, dist[i * n + n]);
    cout << ans;
    return 0;
}
