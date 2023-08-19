#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3000;
long long n, m, k, w[N];
vector<int> g[N];

void bfs(int s, int dis[])
{
    queue<int> q;
    q.emplace(s), dis[s] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (dis[u] == k + 1)
            continue;
        for (int v : g[u])
            if (dis[v] > dis[u] + 1)
                dis[v] = dis[u] + 1, q.emplace(v);
    }
}

int dis[N][N];
set<pair<long long, int>> rch[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 2; i <= n; i++)
        cin >> w[i];
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= n; i++)
        bfs(i, dis[i]);
    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= n; j++)
        {
            if (j == i)
                continue;
            if (dis[i][j] <= k + 1 && dis[1][j] <= k + 1)
                rch[i].emplace(w[j], j);
            if (rch[i].size() > 3)
                rch[i].erase(rch[i].begin());
        }
    long long ans = 0;
    for (int b = 2; b <= n; b++)
        for (int c = 2; c <= n; c++)
        {
            if (b == c || dis[b][c] > k + 1)
                continue;
            for (const auto &[_, a] : rch[b])
            {
                if (a == b || a == c)
                    continue;
                for (const auto &[_, d] : rch[c])
                {
                    if (d == b || d == c || d == a)
                        continue;
                    ans = max(ans, w[b] + w[c] + w[a] + w[d]);
                }
            }
        }
    cout << ans;
    return 0;
}