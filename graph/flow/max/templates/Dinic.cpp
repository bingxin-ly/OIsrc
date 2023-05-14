#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 210, M = 5e3 + 10;
namespace dinic
{
    struct edge
    {
        int v, nxt, cap, flow;
    } e[M << 1];

    int head[N], cnt;

    int n, s, t;
    int dep[N], cur[N];

    void init(int n_, int s_, int t_)
    {
        n = n_, s = s_, t = t_, cnt = 0;
        memset(head, -1, sizeof(head));
    }

    void contact(int u, int v, int w)
    {
        e[cnt] = {v, head[u], w, 0}, head[u] = cnt++;
        e[cnt] = {u, head[v], 0, 0}, head[v] = cnt++;
    }

    bool bfs()
    {
        memset(dep, 0, (n + 1) * sizeof(int));
        dep[s] = 1;
        queue<int> q;
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = head[u]; ~i; i = e[i].nxt)
            {
                int v = e[i].v;
                if (!dep[v] && e[i].cap > e[i].flow)
                {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                }
            }
        }
        return dep[t];
    }

    int dfs(int u, int flow)
    {
        if (u == t || !flow)
            return flow;

        int ret = 0;
        for (int &i = cur[u]; ~i; i = e[i].nxt)
        {
            int v = e[i].v, d;
            if ((dep[v] == dep[u] + 1) &&
                (d = dfs(v, min(flow - ret, e[i].cap - e[i].flow))))
            {
                ret += d;
                e[i].flow += d, e[i ^ 1].flow -= d;
                if (ret == flow)
                    return ret;
            }
        }
        return ret;
    }

    int dinic()
    {
        int maxflow = 0;
        while (bfs())
        {
            memcpy(cur, head, (n + 1) * sizeof(int));
            maxflow += dfs(s, 0x3f3f3f3f);
        }
        return maxflow;
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    dinic::init(n, s, t);
    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dinic::contact(u, v, w);
    }
    cout << dinic::dinic();
    return 0;
}