#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int n, l, r, a[N], f[N];
int hh, tt, q[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> l >> r;
    for (int i = 0; i <= n; i++)
        cin >> a[i];
    memset(f, ~0x3f, sizeof(f));
    f[0] = a[0];
    hh = 0, tt = -1;
    for (int i = l; i <= n; i++)
    {
        if (hh <= tt && q[hh] < i - r)
            hh++;
        while (hh <= tt && f[q[tt]] < f[i - l])
            tt--;
        q[++tt] = i - l;
        f[i] = f[q[hh]] + a[i];
        // 这不就是在一段数中找出一个最大值
        // for (int j = max(0, i - r); j <= i - l; j++)
        //     f[i] = max(f[i], f[j] + a[i]);
    }
    int ans = ~0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        if (i + r > n)
            ans = max(ans, f[i]);
    cout << ans;
    return 0;
}