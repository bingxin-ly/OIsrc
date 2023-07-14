/* 分组背包但是求方案数版，就像数字组合，max改求和即可 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105, MOD = 1e6 + 7;
int n, m, a[N];

namespace search
{
    int f[N][N];
    int solve(int x, int s)
    {
        if (s > m)
            return 0;
        if (x == n + 1)
            return s == m;
        if (f[x][s] != -1)
            return f[x][s];
        int ans = 0;
        for (int k = 0; k <= a[x]; k++)
            (ans += solve(x + 1, s + k)) %= MOD;
        return f[x][s] = ans;
    }
}
namespace knapsack
{
    int f[N];
    signed main()
    {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        f[0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = m; j >= 0; j--)
                for (int k = 1; k <= min(a[i], j); k++)
                    // 0 就是不选，不用显式枚举了
                    (f[j] += f[j - k]) %= MOD;
        cout << f[m];
        return 0;
    }
}
namespace optimized
{
    int s[N], f[N];
    signed main()
    {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        f[0] = s[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                s[j] = (s[j - 1] + f[j]) % MOD;
            for (int j = m; j >= 1; j--)
            {
                int t = j - min(a[i], j) - 1;
                (f[j] += s[j - 1] - s[t] * (t >= 0) + MOD) %= MOD;
            }
        }
        cout << f[m];
        return 0;
    }
}
signed main() { return optimized::main(); }