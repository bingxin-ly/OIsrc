#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

inline int input()
{
    int p = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        p = p * 10 + c - '0', c = getchar();
    return p;
}

const int N = 1e3 + 10;
int n, m, c, moni[N];
vector<pair<int, int>> graph[N];

int q1[5 * N * N], q2[5 * N * N];
int ans[N], dist[N][5 * N], vis[N][5 * N];
void SPFA()
{
    memset(dist, ~0x3f, sizeof(dist));
    memset(ans, ~0x3f, sizeof(ans));
    dist[1][0] = 0;
    vis[1][0] = true;

    int hh = 0, tt = 0;
    q1[++tt] = 1, q2[tt] = 0;

    while (hh < tt && tt <= 5e6)
    {
        int t1 = q1[++hh], t2 = q2[hh];
        vis[t1][t2] = false;
        for (auto i : graph[t1])
        {
            int len = dist[t1][t2] + i.y - c * (t2 + t2 + 1);
            if (dist[i.x][t2 + 1] < len && ans[i.x] < len)
            {
                dist[i.x][t2 + 1] = ans[i.x] = len;
                if (!vis[i.x][t2 + 1])
                {
                    vis[i.x][t2 + 1] = true;
                    q1[++tt] = i.x, q2[tt] = t2 + 1;
                }
            }
        }
    }
}

int main()
{
    n = input(), m = input(), c = input();
    for (int i = 1; i <= n; i++)
        moni[i] = input();
    for (int i = 1; i <= m; i++)
    {
        int u = input(), v = input();
        graph[u].push_back({v, moni[v]});
    }

    SPFA();

    printf("%d\n", ans[1]);
    return 0;
}
