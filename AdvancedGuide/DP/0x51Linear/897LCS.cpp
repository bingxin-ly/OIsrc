/* 今天写 LCS，是因为遇到了一道题：https://www.luogu.com.cn/problem/P1435
   直接写结论吧，竟然回文的问题也可以转化成两个串的最长公共子序列！
   回文，本质而言，就是正着读和反着读都是一样的，（我竟然之前一直都以对称的角度去看
   所以对于这道题而言，构建一个原串的反串，除去两者相同的公共部分，
   剩下的就是需要修修补补的，长度就求出来了
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
int n, m, f[N][N];
char a[N], b[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    cin >> (a + 1) >> (b + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i] == b[j])
                f[i][j] = f[i - 1][j - 1] + 1;
            else
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
    cout << f[n][m];
    return 0;
}