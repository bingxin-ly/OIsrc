#include <bits/stdc++.h>
#define mod(_x, _p) ((_x) % (_p) + (_p)) % (_p)
using namespace std;

constexpr int N = 10005, K = 105;
int n, k, a[N], f[2][K];
void solve()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i], a[i] = mod(a[i], k);
    memset(f, 0, sizeof(f));
    f[1][mod(a[1], k)] = 1;
    for (int i = 2; i < n; i++)
    {
        for (int j = 0; j < k; j++)
            if (f[i & 1][j])
                f[(i + 1) & 1][mod(j + a[i], k)] =
                    f[(i + 1) & 1][mod(j - a[i], k)] = true;
        memset(f[i & 1], 0, sizeof(f[i & 1]));
    }
    cout << (f[n & 1][0] ? "Divisible\n" : "Not divisible\n");
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}