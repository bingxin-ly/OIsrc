/* 贪心优化 DP，题目描述十分清晰，可以直接套多重背包优化的板子，不过，
   题目中没有价值这个维度，只考虑可行性，我们可以发现如果一个面值能拼出来，
   既可能不用 i 就行，也可能减去一些值使用几个 i 才能拼出来，
   我们就考虑贪心地让面值 j 使用的硬币数尽量少。
   也就是说，f[j] 与 f[j - a[i]]都为 true 时，不转移，并令 use[j] = 0;
   否则才由之前的面值得到，并更新 use[j] = use[j - a[i]] + 1;
   实现时采用完全背包的循环模型，且用 use 控制次数，
   同时 f[j] 为 false 时进行转移，保证了不会漏掉可行解。
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105, M = 1e5 + 5;
int n, m, a[N], c[N], use[M];
bool f[M];

void force()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= c[i]; j++)
            for (int k = m; k >= a[i]; k--)
                f[k] |= f[k - a[i]];
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans += f[i];
    cout << ans << '\n';
}
void solve()
{
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        memset(use, 0, (m + 1) * sizeof(int));
        for (int j = a[i]; j <= m; j++)
            if (!f[j] && f[j - a[i]] && use[j - a[i]] < c[i])
                f[j] = true, use[j] = use[j - a[i]] + 1;
    }
    int ans = 0;
    for (int j = 1; j <= m; j++)
        ans += f[j];
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m, n || m)
    {
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            cin >> c[i];
        solve();
    }
    return 0;
}