#include <bits/stdc++.h>
using namespace std;

constexpr int N = 35, M = 105, MOD = 998244353;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    static long long C[N][N];
    {
        for (int i = 0; i <= 30; i++)
            C[i][0] = 1;
        for (int i = 1; i <= 30; i++)
            for (int j = 1; j <= i; j++)
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    static long long n, m, K, v[M], pdt[M][N];
    cin >> n >> m >> K;
    for (int i = 0; i <= m; i++)
    {
        cin >> v[i], pdt[i][0] = 1;
        for (int j = 1; j <= n; j++)
            pdt[i][j] = pdt[i][j - 1] * v[i] % MOD;
    }
    static long long ans, dp[M][N][N][16];
    dp[0][0][0][0] = 1;
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= K; k++)
                for (int p = 0; p <= n >> 1; p++)
                    for (int t = 0; t <= n - j; t++)
                        (dp[i + 1][j + t][k + ((t + p) & 1)][(t + p) >> 1] +=
                         dp[i][j][k][p] * pdt[i][t] % MOD * C[n - j][t] % MOD) %= MOD;
    for (int k = 0; k <= K; k++)
        for (int p = 0; p <= n >> 1; p++)
            if (k + __builtin_popcount(p) <= K)
                (ans += dp[m + 1][n][k][p]) %= MOD;
    cout << ans;
    return 0;
}