#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace MPM
{
    const int flow_inf = 1e18;
    struct edge
    {
        int u, v, cap, flow;
    };

    vector<edge> edges;
    vector<char> alive;
    vector<int> ex, pin, pout;
    vector<int> q, dep;
    vector<list<int>> in, out;
    vector<vector<int>> adj;

    int n, m, s, t;
    int qh, qt;

    void resize()
    {
        ex.resize(n);
        q.resize(n);
        pin.resize(n);
        pout.resize(n);
        adj.resize(n);
        dep.resize(n);
        in.resize(n);
        out.resize(n);
    }

    void init(int n_, int s_, int t_)
    {
        n = n_, s = s_, t = t_;
        resize();
    }

    void contact(int u, int v, int cap)
    {
        edges.push_back({u, v, cap}), adj[u].push_back(m++);
        edges.push_back({v, u, 0}), adj[v].push_back(m++);
    }

    bool bfs()
    {
        while (qh < qt)
        {
            int u = q[qh++];
            for (int id : adj[u])
            {
                auto &e = edges[id];
                if (e.cap - e.flow < 1)
                    continue;
                if (dep[e.u] != -1)
                    continue;
                dep[e.u] = dep[u] + 1;
                q[qt++] = e.u;
            }
        }
        return dep[t] != -1;
    }

    inline int pot(int v) { return min(pin[v], pout[v]); }
    
}