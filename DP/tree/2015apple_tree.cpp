#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int n, m, f[N][N];
vector<pair<int, int>> tr[N];

void dp(int u, int p, int s)
{
    f[u][0] = 0;
    for (const auto &[v, w] : tr[u])
    {
        if (v == p)
            continue;
        dp(v, u, w);
        for (int j = m; j; j--)
            for (int k = 1; k <= j; k++)
                f[u][j] = max(f[u][j], f[u][j - k] + f[v][k]);
    }
    if (u != 1)
        for (int j = m; j; j--)
            f[u][j] = f[u][j - 1] + s;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, tr[u].emplace_back(v, w), tr[v].emplace_back(u, w);
    memset(f, ~0x3f, sizeof(f));
    dp(1, 0, 0);
    cout << f[1][m];
    return 0;
}