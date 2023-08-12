#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e3 + 5, M = 2e3 + 5;
int n, m, u[M], v[M];
vector<int> e[N];
vector<pair<int, int>> g[N];

bool vis[N], con[N];
void dfs(int u)
{
    vis[u] = true;
    for (int v : e[u])
    {
        if (!vis[v])
            dfs(v);
        con[u] |= con[v];
    }
}
int dis[N], len[N];
queue<int> q;
void SPFA()
{
    memset(vis, 0, sizeof(vis)), memset(dis, 0x3f, sizeof(dis)), dis[1] = 0;
    q.emplace(1);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (const auto &[v, w] : g[u])
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w, len[v] = len[u] + 1;
                if (len[v] == n)
                    cout << -1, exit(0);
                if (!vis[v])
                    q.emplace(v), vis[v] = true;
            }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> u[i] >> v[i], e[u[i]].emplace_back(v[i]);
    con[n] = true, dfs(1);
    if (!con[1])
        cout << -1, exit(0);
    for (int i = 1; i <= m; i++)
        if (con[u[i]] && con[v[i]])
            g[u[i]].emplace_back(v[i], 9), g[v[i]].emplace_back(u[i], -1);
    SPFA();
    cout << n << ' ' << m << '\n';
    for (int i = 1; i <= m; i++)
        cout << u[i] << ' ' << v[i] << ' '
             << (con[u[i]] && con[v[i]] ? dis[v[i]] - dis[u[i]] : 1) << '\n';
    return 0;
}