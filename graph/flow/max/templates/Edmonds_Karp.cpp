#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 210;
struct edge
{
    int from, to, cap, flow;
};

struct EK
{
    int m;                // 边数
    vector<edge> edges;   // 边集
    vector<int> graph[N]; // 简单的 vec存边（的下标）
    int max[N], near[N];

    void init(int n)
    {
        for (int i = 0; i < n; i++)
            graph[i].clear();
        edges.clear();
    }

    void contact(int u, int v, int w)
    {
        edges.push_back({u, v, w, 0}), edges.push_back({v, u, 0, 0});
        m = edges.size();
        graph[u].push_back(m - 2), graph[v].push_back(m - 1);
    }

    int max_flow(int s, int t)
    {
        int flow = 0;
        while (true)
        {
            memset(max, 0, sizeof(max));
            queue<int> q;
            q.push(s);
            max[s] = 0x7f7f7f7f;
            while (!q.empty())
            {
                auto x = q.front();
                q.pop();

                for (auto &i : graph[x])
                {
                    auto &e = edges[i];
                    int v = e.to;
                    if (!max[v] && e.cap > e.flow)
                    {
                        near[v] = i;
                        max[v] = min(max[x], e.cap - e.flow);
                        q.push(v);
                    }
                }
                if (max[t])
                    break;
            }
            if (!max[t])
                break;
            for (int u = t; u != s; u = edges[near[u]].from)
            {
                edges[near[u]].flow += max[t];
                edges[near[u] ^ 1].flow -= max[t];
            }
            flow += max[t];
        }
        return flow;
    }
} flow;

signed main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    flow.init(n);
    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        flow.contact(u, v, w);
    }
    cout << flow.max_flow(s, t) << endl;
    return 0;
}
