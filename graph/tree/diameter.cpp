#include <bits/stdc++.h>
#define chkmax(a, b) a = max(a, b)
using namespace std;

const int MAX = 1e6 + 10;

struct edge
{
    int to, w;
};
vector<edge> graph[MAX];
int n, depth[MAX];
int d, d1[MAX], d2[MAX];

inline void add(int u, int v, int w = 1)
{
    graph[u].push_back({v, w});
}
// 仅限于边权全为正！
void dfs(int u, int p)
{
    for (auto i : graph[p])
        if (i.to == u)
            depth[u] = depth[p] + i.w;
    // cout << p << "~" << u << ": " << i.w << endl;
    for (auto i : graph[u])
        if (i.to != p)
            dfs(i.to, u);
}
void dp(int u, int p)
{
    d1[u] = d2[u] = 0;
    for (auto i : graph[u])
    {
        if (i.to == p)
            continue;
        dp(i.to, u);
        int t = d1[i.to] + i.w;
        if (t > d1[u])
            d2[u] = d1[u], d1[u] = t;
        else if (t > d2[u])
            d2[u] = t;
    }
    chkmax(d, d1[u] + d2[u]);
}

int dp_proc()
{
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
    {
        cin >> u >> v >> w;
        add(0, i, 0), add(u, v, w), add(v, u, w);
    }
    dp(1, 0);
    cout << d;
    return 0;
}
int double_bfs()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
    {
        cin >> u >> v >> w;
        add(0, i, 0), add(u, v, w), add(v, u, w);
    }
    dfs(1, 0);
    int l = 1;
    for (int i = 2; i <= n; i++)
        if (depth[i] > depth[l])
            l = i;
    depth[l] = 0;
    dfs(l, 0);
    int r = 1;
    for (int i = 2; i <= n; i++)
        if (depth[i] > depth[r])
            r = i;
    cout << depth[r] << endl;
    return 0;
}