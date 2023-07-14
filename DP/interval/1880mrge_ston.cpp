#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205;
int n, a[N], f[N][N], g[N][N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, x; i <= n; i++)
        cin >> x, a[i] = a[i + n] = x;
    n <<= 1;
    memset(f, ~0x3f, sizeof(f)), memset(g, 0x3f, sizeof(g));
    for (int i = 1; i <= n; i++)
        f[i][i] = g[i][i] = 0, a[i] += a[i - 1];
    for (int l = 2; l <= n; l++)
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            for (int k = i; k < j; k++)
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + (a[j] - a[i - 1])),
                g[i][j] = min(g[i][j], g[i][k] + g[k + 1][j] + (a[j] - a[i - 1]));
        }
    n >>= 1;
    int mans = ~0x3f3f3f3f, nans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        mans = max(mans, f[i][i + n - 1]),
        nans = min(nans, g[i][i + n - 1]);
    cout << nans << '\n'
         << mans;
    return 0;
}