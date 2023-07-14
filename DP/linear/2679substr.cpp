#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005, M = 205, MOD = 1e9 + 7;
int n, m, k, f[M][M][2];
char a[N], b[M];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    cin >> (a + 1) >> (b + 1);

    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            for (int p = 1; p <= k; p++)
            {
                if (a[i] == b[j]) // 可以选或不选
                {
                    f[j][p][0] = (f[j][p][0] + f[j][p][1]) % MOD;
                    f[j][p][1] = ((f[j - 1][p][1] + f[j - 1][p - 1][0]) % MOD +
                                  f[j - 1][p - 1][1]) % MOD;
                }
                else
                {
                    f[j][p][0] = (f[j][p][0] + f[j][p][1]) % MOD;
                    f[j][p][1] = 0;
                }
            }
    cout << (f[m][k][0] + f[m][k][1]) % MOD;
    return 0;
}