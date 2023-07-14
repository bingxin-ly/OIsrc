/* 上古题
   考虑到一个人有两个决策，但只有这两个决策状态也不好转移
   考虑多维护一维状态表示这个人是从哪里进去的，就好决策了
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005, MOD = 19650827;
int n, a[N], f[N][N][2];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        f[i][i][0] = 1;
    for (int l = 2; l <= n; l++)
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            if (a[j] > a[j - 1])
                (f[i][j][1] += f[i][j - 1][1]) %= MOD;
            if (a[j] > a[i])
                (f[i][j][1] += f[i][j - 1][0]) %= MOD;
            if (a[i] < a[i + 1])
                (f[i][j][0] += f[i + 1][j][0]) %= MOD;
            if (a[i] < a[j])
                (f[i][j][0] += f[i + 1][j][1]) %= MOD;
        }
    cout << (f[1][n][0] + f[1][n][1]) % MOD;
    return 0;
}