#include <bits/stdc++.h>
using namespace std;

const int MAX = 5e3 + 10;
struct edge
{
    int v, w, next;
} e[2 * MAX];
int head[MAX], tot[MAX], dis[MAX], vis[MAX];
int n, m, cnt;

inline void addedge(int u, int v, int w)
{
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}
bool spfa(int s)
{
    queue<int> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, vis[s] = 1;
    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if (dis[v] > dis[u] + e[i].w)
            {
                dis[v] = dis[u] + e[i].w;
                if (!vis[v])
                {
                    vis[v] = 1, tot[v]++;
                    if (tot[v] == n + 1)
                        return false;
                    q.push(v);
                }
            }
        }
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        addedge(0, i, 0); // 虚点0
    for (int i = 1; i <= m; i++)
    {
        int v, u, w;
        cin >> v >> u >> w;
        addedge(u, v, w);
    }
    if (!spfa(0))
        cout << "NO" << endl;
    else
        for (int i = 1; i <= n; i++)
            cout << dis[i] << ' ';
    return 0;
}
