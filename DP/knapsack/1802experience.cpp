#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e3 + 5;
int n, x, los[N], win[N], use[N];
int f[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
        cin >> los[i] >> win[i] >> use[i];
    for (int i = 1; i <= n; i++)
        for (int j = x; j >= 0; j--) // 注意 j 取 0
        {
            if (j >= use[i])
                f[j] = max(f[j] + los[i], f[j - use[i]] + win[i]);
            else
                f[j] += los[i];
            // use可能为 0，如果先加 lose就可能 f[j]被更新两边
            // 所以要严格用 if 分开
        }
    cout << 5ll * f[x];
    return 0;
}