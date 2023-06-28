#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int w[N], f[N], q[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    // f[i] = min{f[j]} + w[i];
    int hh = 0, tt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (q[hh] < i - m)
            hh++;
        f[i] = f[q[hh]] + w[i];
        while (hh <= tt && f[q[tt]] >= f[i])
            tt--;
        q[++tt] = i;
    }
    // ×：cout << f[n]; // 状态设计是让最后一个烽火台点燃！记得从最后 m 烽火台里选
    int ans = INT_MAX;
    for (int i = n - m + 1; i <= n; i++)
        ans = min(ans, f[i]);
    cout << ans;
    return 0;
}