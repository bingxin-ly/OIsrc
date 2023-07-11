/* 每一组内 c[i] 个物品的循环 k 应该放在 j 的内层，防止转移时物品的积累；
   从动态规划的原则，i 是 “阶段” ，i 与 j 共同构成 “状态” ，k 是 “决策”
   这三者之间有严格的顺序。
   在这一章背包问题中，我们使用了大量的滚动数组优化空间，
   同时通过循环顺序保证了在各个阶段间的转移是正确的。
   “请读者不要只把正确的循环顺序记住了事，务必要理解清楚其中的本质和内在联系。” ——lyd
   共勉。
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int n, m, s[N], v[N][N], w[N][N], f[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        for (int j = 1; j <= s[i]; j++)
            cin >> v[i][j] >> w[i][j];
    }
    for (int i = 1; i <= n; i++)
        for (int j = m; j; j--)
            for (int k = 1; k <= s[i]; k++)
                if (j >= v[i][k])
                    f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
    cout << f[m];
    return 0;
}