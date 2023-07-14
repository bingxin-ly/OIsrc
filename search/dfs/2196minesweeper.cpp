#include <bits/stdc++.h>
using namespace std;

constexpr int N = 25;
int n, w[N], ans;
bool g[N][N], vis[N];
vector<int> cur, pah;

void dfs(int u, int res)
{
    res += w[u], cur.emplace_back(u), vis[u] = true;
    bool flag = false;
    for (int v = 1; v <= n; v++)
        if (g[u][v] && !vis[v])
            flag = true, dfs(v, res);
    if (!flag && res > ans)
        ans = res, pah = cur;
    cur.pop_back();
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            cin >> g[i][j];
    for (int i = 1; i <= n; i++)
    {
        memset(vis, 0, sizeof(vis));
        dfs(i, 0);
    }
    for (int i : pah)
        cout << i << ' ';
    cout << '\n'
         << ans;
    return 0;
}