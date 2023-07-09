#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

constexpr int N = 1500, MOD = 1e7 + 7;
int c[N], f[N];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int sum = 0;
    for (int i = 1; i <= n; i++)
        cin >> c[i], sum += c[i];

    if (m >= sum)
        cout << 1, exit(0);

    sort(c + 1, c + n + 1);
    int ans = 0;
    f[0] = 1;
    for (int i = n; i >= 1; i--)
    {
        sum -= c[i];
        for (int j = max((m - sum) - (c[i] - 1), 0); j <= m - sum; j++)
            (ans += f[j]) %= MOD;
        for (int j = m; j >= c[i]; j--)
            (f[j] += f[j - c[i]]) %= MOD;
    }
    cout << ans;
    return 0;
}