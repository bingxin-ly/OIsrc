#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e3 + 5, V = 2e4, MOD = 998244353;
int n, h[N], f[N][(V + 5) << 1];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        (ans += 1) %= MOD;
        for (int j = 1; j < i; j++)
        {
            int d = h[i] - h[j];
            (f[i][d + V] += f[j][d + V] + 1) %= MOD;
            (ans += f[j][d + V] + 1) %= MOD;
        }
    }
    cout << ans;
    return 0;
}