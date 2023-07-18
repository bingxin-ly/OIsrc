/* 从上向下考虑，使用了刷表法
   注意题目中有负数
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
int n, a[N][N], f[N][N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            cin >> a[i][j];
    memset(f, ~0x3f, sizeof(f));
    f[1][1] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= i; j++)
            f[i + 1][j] = max(f[i + 1][j], f[i][j] + a[i][j]),
                  f[i + 1][j + 1] = max(f[i + 1][j + 1], f[i][j] + a[i][j]);
    int ans = ~0x3f3f3f3f;
    for (int j = 1; j <= n; j++)
        ans = max(ans, f[n][j] + a[n][j]);
    cout << ans;
    return 0;
}