#include <bits/stdc++.h>
using namespace std;

constexpr int N = 505;
int n, a[N], f[N][N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], f[i][i] = 1;
    for (int i = 1; i < n; i++)
        f[i][i + 1] = 1 + (a[i] != a[i + 1]);
    for (int l = 3; l <= n; l++)
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            f[i][j] = 0x3f3f3f3f;
            if (a[i] == a[j])
                f[i][j] = f[i + 1][j - 1];
            for (int k = i; k < j; k++)
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
        }
    cout << f[1][n];
    return 0;
}