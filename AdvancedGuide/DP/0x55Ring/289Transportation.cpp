/* 存两倍型的环形处理，使用单调队列优化
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e6 + 5;
int n, a[N], q[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], a[i + n] = a[i];
    int h = 1, t = 1, ans = 0;
    q[1] = 0; // 单调队列，存 a[i] - i
    for (int i = 1; i <= n << 1; i++)
    {
        while (h <= t && q[h] < i - (n >> 1))
            h++;
        ans = max(ans, a[i] + i + a[q[h]] - q[h]);
        while (h <= t && a[q[t]] - q[t] <= a[i] - i)
            t--;
        q[++t] = i;
    }
    cout << ans;
    return 0;
}