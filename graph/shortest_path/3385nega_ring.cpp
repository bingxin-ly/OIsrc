#include <bits/stdc++.h>
using namespace std;

const int N = 3e3 + 10;
int n, m;
int dis[N], cnt[N];
bool vis[N];
struct edge
{
    int to, w;
};
vector<edge> graph[N];

inline void add(int u, int v, int w = 1)
{
    graph[u].push_back({v, w});
}

bool spfa(int s)
{
    queue<int> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, vis[s] = true;
    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (auto i : graph[u])
        {
            int v = i.to;
            if (dis[v] > dis[u] + i.w)
            {
                dis[v] = dis[u] + i.w;
                if (!vis[v])
                {
                    vis[v] = 1, cnt[v]++;
                    if (cnt[v] == n + 1)
                        return true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
            graph[i].clear();
        memset(cnt, 0, sizeof(cnt));
        memset(vis, 0, sizeof(vis));
        for (int i = 1, u, v, w; i <= m; i++)
        {
            cin >> u >> v >> w;
            if (w >= 0)
                add(u, v, w), add(v, u, w);
            else
                add(u, v, w);
        }
        cout << (spfa(1) ? "YES" : "NO") << endl;
    }
    return 0;
}