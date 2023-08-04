#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e2 + 5;
int n, in[N], vis[N];
vector<int> g[N], topo;

void dfs(int u)
{
    topo.emplace_back(u), vis[u] = 1;
    for (int v : g[u])
        if (!--in[v])
            dfs(v);
}
void bfs()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i])
            q.emplace(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), topo.emplace_back(u);
        for (int v : g[u])
            if (!--in[v])
                q.push(v);
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, s; i <= n; i++)
        while (cin >> s, s)
            g[i].emplace_back(s), in[s] += 1;
    // bfs();
    for (int i = 1; i <= n; i++)
        if (!in[i] && !vis[i])
            dfs(i);
    for (int i : topo)
        cout << i << ' ';
    return 0;
}