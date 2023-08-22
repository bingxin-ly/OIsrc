#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
int n, m, w[N][N];
int dis[N], vis[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    memset(w, 0x3f, sizeof(w));
    for (int i = 1; i <= n; i++)
        w[i][i] = 0;
    for (int i = 1, u, v, w_; i <= m; i++)
        cin >> u >> v >> w_, w[u][v] = w[v][u] = min(w[u][v], w_);
    memset(dis, 0x3f, sizeof(dis)), dis[1] = 0;
    for (int _ = 1; _ < n; _++)
    {
        int u = 0;
        for (int i = 1; i <= n; i++)
            if (!vis[i] && (!u || dis[i] < dis[u]))
                u = i;
        vis[u] = 1;
        for (int v = 1; v <= n; v++)
            dis[v] = min(dis[v], dis[u] + w[u][v]);
    }
    memset(vis, 0, sizeof(vis)), vis[1] = 1;
    long long ans = 1;
    for (int _ = 1; _ < n; _++)
    {
        int v = 0, k = 0;
        for (int i = 1; i <= n; i++)
            if (!vis[i] && (!v || dis[i] < dis[v]))
                v = i;
        for (int u = 1; u <= n; u++)
            if (vis[u] && dis[v] == dis[u] + w[u][v])
                k++;
        vis[v] = 1, (ans *= k) %= INT_MAX;
    }
    cout << ans;
    return 0;
}