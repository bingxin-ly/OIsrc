#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, dis[N];
vector<pair<int, int>> g[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w);
    memset(dis, 0x7f, sizeof(dis)), dis[1] = 0;
    for (int i = 1; i < n; i++) // 扩展 n - 1 次
    {
        bool flag = false;
        for (int u = 1; u <= n; u++)
            for (const auto &[v, w] : g[u])
                // dis[v] = min(dis[v], dis[u] + w);
                if (dis[v] > dis[u] + w)
                    dis[v] = dis[u] + w, flag = true;
        if (!flag)
            break;
    }
    if (dis[n] != 0x7f7f7f7f)
        cout << dis[n];
    else
        cout << "impossible";
    return 0;
}