/* 最长下降子序列什么的好说，问题在于统计方案数，而且还要去重
   如果不要求去重的话，对于合法的转移，我们来个 sigma 求和即可
   问题在于怎么搞掉数一样的序列？？？
   设 i, j, k, k < j < i 且 a[k] > a[j] a[k] > a[i]，
   人话即 j、i 处的 f 是由 k 导出来的。
   当我们发现 f[j] == f[i] 且 a[j] == a[i]，这说明 k 非常高产，
   一下导出来两个 f，而这是非常危险的，一样的多了就容易计重。
   所以我们考虑只保留一个位置，把 j 处的 c 值置 0，也就是这两个我们只保留后面的
   而这么做也是有原因的，对于这样的等效位置 j、i，i 是 包含 j 的
   考虑这样一个序列 6 7 5 3 *2* 4 *2* 对于这两个 2，都可以由 6 5 3 _ 得到
   但由于后面的 2 更靠后，包含了前面的 2 没有的 6 5 4 2，情况更多，所以保留
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5005;
int n, a[N], f[N], c[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    memset(f, ~0x3f, sizeof(f));
    a[0] = 1 << 30, f[0] = 0, c[0] = 1; // 我们把初态设到 0，这样简单
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
            if (a[j] > a[i])
            {
                if (f[i] < f[j] + 1)
                    f[i] = f[j] + 1, c[i] = c[j]; // 继承过来
                else if (f[i] == f[j] + 1)
                    c[i] += c[j];
            }
            else if (a[j] == a[i])
                c[j] = 0;
    }
    int ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++)
        if (f[i] > ans)
            ans = f[i], cnt = c[i];
        else if (f[i] == ans)
            cnt += c[i];
    cout << ans << ' ' << cnt;
    return 0;
}