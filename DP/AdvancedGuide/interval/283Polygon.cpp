/* 这题给我们两个注意点：
   1. 找最优子结构是 DP 永远绕不过去的。我们分析发现单纯的 f[l][r] 并不足以转移我们的最优解，
      加法没问题，问题就在于合并时有乘，一个最大值乘上一个最小值立即就变成最劣解了。
      这说明我们维护的信息还不足以支撑转移，我们考虑负负得正，再在此基础上维护一个最小值，
      设 y1 <= z <= x1, y2 <= z' <= x2 且符号为乘时
      若 z' >= 0, y1*z' <= z*z' <= x1*z' 此时出现子问题
      若 z' < 0, y1*z' >= z*z' >= x1*z' 仍为子问题
      故在任何情况下，大区间的最大最小值都是子区间的最大最小值四个乘积中之一，这样就解决了维护的问题
   2. 成链后搞区间 DP 没问题了，但原问题是一个环。题目提示当然可以枚举第一条断掉的边，
      但这样有很多区间被重复计算了，复杂度不优。我们可以随意断掉一条边之后在后边复制一倍，
      转化为一个长度为 2n 的链，这样可以照顾到所有跨越一个断边的区间，最后再枚举长度为 n 的区间，
      得出答案。
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 55 << 1;
int n, f[N][N][2]; // 0 代表最大，1 代表最小
char ope[N];

inline int max(int x, int y) { return x > y ? x : y; }
inline int min(int x, int y) { return x < y ? x : y; }
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    char op;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> op >> x;
        ope[i] = ope[i + n] = op;
        f[i][i][0] = f[i][i][1] = f[i + n][i + n][0] = f[i + n][i + n][1] = x;
    }
    n <<= 1;
    for (int len = 2; len <= n; len++)
        for (int l = 1; l <= n - len + 1; l++)
        {
            int r = l + len - 1;
            f[l][r][0] = ~0x3f3f3f3f, f[l][r][1] = 0x3f3f3f3f;
            for (int k = l; k < r; k++)
            {
                // merge f[l, k] f[k + 1, r]
                if (ope[k + 1] == 't')
                {
                    f[l][r][0] = max(f[l][r][0], f[l][k][0] + f[k + 1][r][0]);
                    f[l][r][1] = min(f[l][r][1], f[l][k][1] + f[k + 1][r][1]);
                }
                else
                {
                    int a = f[l][k][0] * f[k + 1][r][0], b = f[l][k][0] * f[k + 1][r][1],
                        c = f[l][k][1] * f[k + 1][r][0], d = f[l][k][1] * f[k + 1][r][1];
                    f[l][r][0] = max(f[l][r][0], max(max(a, b), max(c, d)));
                    f[l][r][1] = min(f[l][r][1], min(min(a, b), min(c, d)));
                }
            }
        }
    n >>= 1;
    int ans = ~0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i][i + n - 1][0]);
    cout << ans << '\n';
    for (int i = 1; i <= n; i++)
        if (f[i][i + n - 1][0] == ans)
            cout << i << ' ';
    return 0;
}