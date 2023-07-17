#include <bits/stdc++.h>
using namespace std;

constexpr int N = 55;
int n, m, w[N][N], f[N][N][31];
signed main()
{
    cin >> n >> m;
    memset(w, 0x3f, sizeof(w));
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, f[u][v][0] = w[u][v] = 1;
    for (int o = 1; o <= 30; o++)
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (f[i][k][o - 1] && f[k][j][o - 1])
                        f[i][j][o] = w[i][j] = 1;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
    cout << w[1][n];
    return 0;
}