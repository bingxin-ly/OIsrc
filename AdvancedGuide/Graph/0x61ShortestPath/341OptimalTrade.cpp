#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5, M = 5e5 + 5;
int n, m, w[N], mn[N], mx[N];
namespace seprate
{
    vector<int> g[N], rg[N];

    bool in[N];
    queue<int> q;
    void spfa(int s)
    {
        q.emplace(s), in[s] = true;
        s == 1 ? mn[s] = w[s] : mx[s] = w[s];
        while (!q.empty())
        {
            int u = q.front();
            q.pop(), in[u] = false;
            if (s == 1)
            {
                for (int v : g[u])
                    if (mn[v] > min(mn[u], w[v]))
                    {
                        mn[v] = min(mn[u], w[v]);
                        if (!in[v])
                            q.emplace(v), in[v] = true;
                    }
            }
            else
            {
                for (int v : rg[u])
                    if (mx[v] < max(mx[u], w[v]))
                    {
                        mx[v] = max(mx[u], w[v]);
                        if (!in[v])
                            q.emplace(v), in[v] = true;
                    }
            }
        }
    }
    signed main()
    {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> w[i];
        for (int i = 1, u, v, z; i <= m; i++)
        {
            cin >> u >> v >> z;
            g[u].emplace_back(v), rg[v].emplace_back(u);
            if (z == 2)
                g[v].emplace_back(u), rg[u].emplace_back(v);
        }
        memset(mn, 0x3f, sizeof(mn)), spfa(1);
        memset(mx, ~0x3f, sizeof(mx)), spfa(n);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans = max(ans, mx[i] - mn[i]);
        cout << ans;
        return 0;
    }
}
namespace fusion
{
    int idx, hed[N], ver[M << 1], tag[M << 1], nxt[M << 1];
    inline void contact(int u, int v, int t)
    {
        ver[++idx] = v, tag[idx] = t;    // 1 代表正向，-1 代表反向，2 代表双向
        nxt[idx] = hed[u], hed[u] = idx; // 这样边数最多还是 2*M 的
    }

    bool in[N];
    queue<int> q;
    void spfa(int s, int *dis, int t)
    {
        q.emplace(s), in[s] = true, dis[s] = w[s];
        while (!q.empty())
        {
            int u = q.front();
            q.pop(), in[u] = false;
            for (int i = hed[u]; i; i = nxt[i])
                if (tag[i] == t || tag[i] == 2)
                {
                    int v = ver[i];
                    int val = t > 0 ? min(dis[u], w[v]) : max(dis[u], w[v]);
                    if ((t > 0 && dis[v] > val) || (t < 0 && dis[v] < val))
                    {
                        dis[v] = val;
                        if (!in[v])
                            q.emplace(v), in[v] = true;
                    }
                }
        }
    }
    signed main()
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> w[i];
        for (int i = 1, u, v, t; i <= m; i++)
        {
            cin >> u >> v >> t;
            if (t == 1)
                contact(u, v, 1), contact(v, u, -1);
            else
                contact(u, v, 2), contact(v, u, 2);
            // std 使用了三目运算符（我也有烦三目的一天啊
        }
        memset(mn, 0x3f, sizeof(mn)), spfa(1, mn, 1);
        memset(mx, ~0x3f, sizeof(mx)), spfa(n, mx, -1);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans = max(ans, mx[i] - mn[i]);
        cout << ans;
        return 0;
    }
}
signed main() { return fusion::main(); }