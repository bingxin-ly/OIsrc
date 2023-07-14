#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int a[N], f[N], g[N];
// f[i] 表示以 i 结尾的最大字段和， g[i] 表示前 i 个数的最大字段和

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    g[0] = ~0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        f[i] = max(f[i - 1] + a[i], a[i]), // 如果可为空填 0，否则是这个数
            g[i] = max(g[i - 1], f[i]);
    cout << g[n];
    return 0;
}
signed implicit() // 实际上还是 DP，眼拙看成贪心了
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    int ans = ~0x3f3f3f3f, cur = 0;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x, cur += x;
        ans = max(ans, cur), cur = max(cur, 0);
    }
    cout << ans;
    return 0;
}