#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
int n, m, p, c[N], w[N][N];
int f[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> w[i][j];
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    memset(f, ~0x3f, sizeof(f)), f[0] = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            int sum = 0;
            for (int k = 1; k <= p && k <= i; k++)
            {
                int lst = j - k;
                if (lst <= 0)
                    lst = lst % n + n;
                sum += w[lst][i - k + 1];
                f[i] = max(f[i], f[i - k] + sum - c[lst]);
            }
        }
    cout << f[m];
    return 0;
}