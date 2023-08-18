#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005, MOD = 998244353;
int n, m, C, F, f[N][N];
char g[N][N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T, id;
    cin >> T >> id;
    while (T--)
    {
        memset(f, 0, sizeof(f));
        cin >> n >> m >> C >> F;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> g[i][j];
        for (int i = 1; i <= n; i++)
            for (int j = m - 1; j >= 1; j--)
                if (g[i][j] == '1')
                    f[i][j] = -1;
                else if (g[i][j + 1] == '0')
                    f[i][j] = f[i][j + 1] + 1;
        int ansc = 0, ansf = 0;
        for (int j = 1; j < m; j++)
        {
            int ccnt = 0, fcnt = 0;
            for (int i = 1; i <= n; i++)
            {
                if (f[i][j] == -1)
                {
                    ccnt = fcnt = 0;
                    continue;
                }
                (ansc += 1ll * f[i][j] * ccnt % MOD) %= MOD, (ansf += fcnt) %= MOD;
                (fcnt += 1ll * f[i][j] * ccnt % MOD) %= MOD, (ccnt += max(f[i - 1][j], 0)) %= MOD;
            }
        }
        cout << C * ansc % MOD << ' ' << F * ansf % MOD << '\n';
    }
    return 0;
}