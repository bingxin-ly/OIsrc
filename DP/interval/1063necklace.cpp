#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205;
int n, a[N], f[N][N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], a[i + n] = a[i];
    n <<= 1;
    for (int l = 2; l <= n; l++)
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            for (int k = i; k < j; k++)
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + a[i] * a[k + 1] * a[j + 1]);
        }
    n >>= 1;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i][i + n - 1]);
    cout << ans;
    return 0;
}