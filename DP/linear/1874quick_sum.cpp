#include <bits/stdc++.h>
using namespace std;

constexpr int L = 45, N = 1e5 + 5;
int n, m, v[L][L], f[L][N];
char s[L];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> (s + 1) >> m;
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        for (int j = i; j <= n; j++)
        {
            val = val * 10 + s[j] - '0';
            v[i][j] = val;
        }
    }
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 1; k <= i; k++)
                if (j >= v[i - k + 1][i])
                    f[i][j] = min(f[i][j], f[i - k][j - v[i - k + 1][i]] + 1);
    cout << (f[n][m] != 0x3f3f3f3f ? f[n][m] - 1 : -1);
    return 0;
}