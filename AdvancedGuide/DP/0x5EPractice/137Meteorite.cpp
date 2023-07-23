#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 11380;
int L1, L2, L3, D;
int f[35][15][15][15];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> L1 >> L2 >> L3 >> D;
    for (int i = 0; i <= D; i++)
        f[i][0][0][0] = 1;
    for (int p = 1; p <= D; p++)
        for (int i = 0; i <= L1; i++)
            for (int j = 0; j <= L2; j++)
                for (int k = 0; k <= L3; k++)
                {
                    if (i) // 最外层括号是 {}
                        for (int u = 1; u <= i; u++)
                            for (int v = 0; v <= j; v++)
                                for (int w = 0; w <= k; w++)
                                    (f[p][i][j][k] += f[p - 1][u - 1][v][w] * f[p][i - u][j - v][k - w] % MOD) %= MOD;
                    if (j) // 最外层括号是 []
                        for (int v = 1; v <= j; v++)
                            for (int w = 0; w <= k; w++)
                                (f[p][i][j][k] += f[p - 1][0][v - 1][w] * f[p][i][j - v][k - w] % MOD) %= MOD;
                    if (k) // 最外层括号是 ()
                        for (int w = 1; w <= k; w++)
                            (f[p][i][j][k] += f[p - 1][0][0][w - 1] * f[p][i][j][k - w]) %= MOD;
                }
    if (D)
        cout << (f[D][L1][L2][L3] - f[D - 1][L1][L2][L3] + MOD) % MOD;
    else
        cout << f[D][L1][L2][L3];
    return 0;
}