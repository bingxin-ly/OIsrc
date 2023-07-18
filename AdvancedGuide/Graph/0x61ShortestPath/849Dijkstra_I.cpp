#include <bits/stdc++.h>
using namespace std;

constexpr int N = 505;
int n, m, s[N][N], dis[N];
bool vis[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    memset(s, 0x7f, sizeof(s));
    for (int i = 1; i <= n; i++)
        s[i][i] = 0;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, s[u][v] = min(s[u][v], w);
    // 自环和重边实质就是长度为 1 和 2 的环，我们这里简单处理一下就行
    memset(dis, 0x7f, sizeof(dis)), dis[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        int minn = 1 << 30, u;
        for (int v = 1; v <= n; v++)
            if (!vis[v] && dis[v] < minn)
                minn = dis[v], u = v;
        vis[u] = true;
        for (int v = 1; v <= n; v++)
            dis[v] = min(dis[v], dis[u] + s[u][v]);
    }
    cout << (dis[n] == 0x7f7f7f7f ? -1 : dis[n]);
    return 0;
}