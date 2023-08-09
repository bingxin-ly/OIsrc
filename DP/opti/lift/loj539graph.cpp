#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
int n, m, C, T, p[N], c[N];
long long g[17][N][N], f[N][N * N], A[N], B[N], D[N][N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> C >> T;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i] >> c[i], c[i] = min(c[i], C);
        for (int j = 1; j <= n; j++)
            g[0][i][j] = -INF * (i != j);
    }
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w,
            g[0][u][v] = max(g[0][u][v], w + 0ll);
    for (int k = 1; k <= 16; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                g[k][i][j] = -INF;
                for (int l = 1; l <= n; l++)
                    g[k][i][j] = max(g[k][i][j], g[k - 1][i][l] + g[k - 1][l][j]);
            }
    for (int i = 1; i <= n; i++)
    {
        memset(A, ~0x3f, sizeof(A)), A[i] = 0;
        for (int k = 16; k >= 0; k--)
            if (c[i] >> k & 1)
            {
                for (int j = 1; j <= n; j++)
                {
                    B[j] = -INF;
                    for (int l = 1; l <= n; l++)
                        B[j] = max(B[j], A[l] + g[k][l][j]);
                }
                memcpy(A, B, sizeof(B));
            }
        memcpy(D[i], A, sizeof(A));
    }
    for (int j = 0; j <= n * n; j++)
        for (int i = 1; i <= n; i++)
            if (j >= p[i])
                for (int k = 1; k <= n; k++)
                    f[i][j] = max(f[i][j], f[k][j - p[i]] + D[i][k]);
    for (int s, q, d; T--;)
    {
        cin >> s >> q >> d;
        int ans = 1;
        while (ans <= q && f[s][ans] < d)
            ans += 1;
        cout << (ans > q ? -1 : q - ans) << '\n';
    }
    return 0;
}