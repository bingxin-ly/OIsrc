#include <bits/stdc++.h>
using namespace std;

int n, m, a[108][108], d[108][108], p[108][108];
vector<int> path;

void access(int i, int j)
{
    if (!p[i][j])
        return;
    access(i, p[i][j]);
    path.emplace_back(p[i][j]);
    access(p[i][j], j);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    memset(a, 0x3f, sizeof(a));
    for (int i = 1; i <= n; i++)
        a[i][i] = 0;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, a[v][u] = a[u][v] = min(a[u][v], w);
    memcpy(d, a, sizeof(a));
    int ans = 0x3f3f3f3f;
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i < k; i++)
            for (int j = i + 1; j < k; j++)
                if (ans > 0ll + d[i][j] + a[j][k] + a[k][i])
                {
                    ans = d[i][j] + a[j][k] + a[k][i];
                    path.clear(), path.emplace_back(i);
                    access(i, j);
                    path.emplace_back(j), path.emplace_back(k);
                }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = d[i][k] + d[k][j], p[i][j] = k;
    }
    if (ans == 0x3f3f3f3f)
        cout << "No solution.";
    else
    {
        for (int i : path)
            cout << i << ' ';
        /* long long ans = 0;
        for (size_t i = 1; i < path.size(); i++)
            ans += a[path[i - 1]][path[i]];
        ans += a[path.back()][path.front()];
        cout << ans; */
    }
    return 0;
}