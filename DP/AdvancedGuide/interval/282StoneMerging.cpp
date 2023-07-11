/* 我之前一直不知道区间断点 k 的枚举范围，今天总算是懂了
   l <= k && k + 1 <= r （两边长度为 1 的元区间都能枚举到）
   所以 k 的范围是 [l, r)
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 305;
int n, s[N], f[N][N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i], s[i] += s[i - 1];
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
        f[i][i] = 0;
    for (int len = 2; len <= n; len++)
        for (int l = 1; l <= n - len + 1; l++)
        {
            int r = l + len - 1;
            for (int k = l; k < r; k++)
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
            f[l][r] += s[r] - s[l - 1];
        }
    cout << f[1][n];
    return 0;
}