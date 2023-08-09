#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e6 + 5, M = 6e6 + 5, S = N - 2, T = N - 1;
int n, m;
vector<pair<int, int>> g[N];

int trans(int x, int y, int z)
{
    if (x < 0 || y >= m - 1)
        return S;
    if (y < 0 || x >= n - 1)
        return T;
    return z + y * 2 + x * (m - 1) * 2;
}

int dis[N];
void dijkstra()
{
    memset(dis, 0x3f, sizeof(dis));
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 0, u, v, w; i < n; i++)
        for (int j = 0; j < m - 1; j++)
            u = trans(i - 1, j, 1), v = trans(i, j, 0), cin >> w,
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    for (int i = 0, u, v, w; i < n - 1; i++)
        for (int j = 0; j < m; j++)
            u = trans(i, j - 1, 0), v = trans(i, j, 1), cin >> w,
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    for (int i = 0, u, v, w; i < n - 1; i++)
        for (int j = 0; j < m - 1; j++)
            u = trans(i, j, 0), cin >> w,
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    dijkstra();

    return 0;
}