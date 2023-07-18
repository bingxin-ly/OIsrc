/* 写了一下午题，发现自己脑子还是那么笨，于是就滚回来了
   考虑转移，题目要求求严格上升子序列，
   可以想到一个子序列可以由一个末尾元素更小的子序列拼接而来。
   记录子序列的每种情况，转移时 n^2 枚举
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
int n, a[N], f[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    a[0] = ~0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i])
                f[i] = max(f[i], f[j] + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i]);
    cout << ans;
    return 0;
}