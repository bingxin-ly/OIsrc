#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

const int N = 5e4 + 10, M = N << 1, INF = 0x3f3f3f3f;
struct
{
    int u, v, a, b;
} g[M];
int idx, head[N], edge[M << 1], val[M << 1], nxt[M << 1];
inline void contact(int u, int v, int w)
{
    nxt[++idx] = head[u], head[u] = idx;
    edge[idx] = v, val[idx] = w;
}

int dis[N], vis[N];
queue<int> *q;
void spfa()
{
    while (!q->empty())
    {
        int u = q->front();
        q->pop();
        vis[u] = false;

        for (int i = head[u]; i; i = nxt[i])
        {
            int v = edge[i];
            if (max(val[i], dis[u]) < dis[v])
            {
                dis[v] = max(val[i], dis[u]);
                if (!vis[v])
                    q->push(v), vis[v] = true;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, ans = INF;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> g[i].u >> g[i].v >> g[i].a >> g[i].b;
    sort(g + 1, g + m + 1, [](const auto &x, const auto &y)
         { return x.a < y.a; });

    memset(dis, 0x3f, sizeof dis), dis[1] = 0;
    for (int i = 1; i <= m; i++)
    {
        contact(g[i].u, g[i].v, g[i].b);
        contact(g[i].v, g[i].u, g[i].b);

        q = new queue<int>();
        q->push(g[i].u), q->push(g[i].v);
        vis[g[i].u] = vis[g[i].v] = true;
        spfa();

        if (dis[n] != INF)
            ans = min(ans, g[i].a + dis[n]);
    }

    cout << (ans == INF ? -1 : ans);
    return 0;
}