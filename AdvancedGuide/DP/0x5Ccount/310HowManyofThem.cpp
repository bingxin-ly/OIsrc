#include <bits/stdc++.h>
using namespace std;

constexpr int N = 51, MOD = 1e9 + 7;
int n, m;
long long f[N][N], g[N][N][N], h[N], C[N][N], B[1250];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    if (m >= n)
        m = n - 1;
    for (int i = 0; i <= n; i++)
        C[i][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    B[0] = 1;
    for (int i = 1; i <= n * (n - 1) / 2; i++)
        B[i] = B[i - 1] * 2 % MOD;

    g[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        h[i] = B[i * (i - 1) / 2];
        for (int j = 1; j < i; j++)
            (h[i] -= h[j] * C[i - 1][j - 1] % MOD * B[(i - j) * (i - j - 1) / 2]) %= MOD;
        f[i][0] = h[i];
        for (int j = 1; j < i; j++)
        {
            for (int k = 1; k < i; k++)
            {
                long long c1 = f[k][0] * C[i - 1][k - 1] % MOD, kx = 1;
                for (int x = 1; x <= min(i - k, j); x++)
                    (kx *= k) %= MOD,
                        (f[i][j] += c1 * g[i - k][j - x][x] % MOD * kx) %= MOD;
            }
            (f[i][0] -= f[i][j]) %= MOD;
        }
        for (int j = 0; j < i; j++)
            for (int p = 1; p <= i; p++)
                for (int q = 0; q <= j; q++)
                {
                    long long c1 = f[p][q] * C[i - 1][p - 1] % MOD * p % MOD;
                    for (int k = 1; k <= i; k++)
                        (g[i][j][k] += c1 * g[i - p][j - q][k - 1]) %= MOD;
                }
    }
    long long ans = 0;
    for (int i = 0; i <= m; i++)
        (ans += f[n][i]) %= MOD;
    cout << (ans + MOD) % MOD;
    return 0;
}