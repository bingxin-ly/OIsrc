#include <bits/stdc++.h>
using namespace std;
typedef long long big;

const int N = 1e5 + 10;
struct edge
{
    int to, w;
};
vector<edge> graph[N];

inline void add(int u, int v, int w = 1)
{
    graph[u].push_back({v, w});
}

queue<int> q;
big dist[N];
bool vis[N];
void spfa()
{
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    dist[1] = 1;

    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        vis[x] = 0;

        for (auto i : graph[x])
        {
            int y = i.to;
            if (dist[y] > dist[x] + i.w)
            {
                dist[y] = dist[x] + i.w;
                if (!vis[y])
                {
                    q.push(y);
                    vis[y] = 1;
                }
            }
        }
    }
}

int main()
{
    big h, x, y, z;
    cin >> h >> x >> y >> z;
    if (x == 1 || y == 1 || z == 1)
        return cout << h, 0;
    for (int i = 0; i < x; i++)
    {
        add(i, (i + y) % x, y);
        add(i, (i + z) % x, z);
    }

    spfa();

    big ans = 0;
    for (int i = 0; i < x; i++)
        if (dist[i] <= h)
            ans += (h - dist[i]) / x + 1;

    cout << ans;
    return 0;
}
