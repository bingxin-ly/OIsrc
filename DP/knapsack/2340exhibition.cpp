#include <bits/stdc++.h>
using namespace std;

constexpr int N = 405, V = 400000;
int n, v[N], w[N], f[2][N * 2000];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];
    memset(f, ~0x3f, sizeof(f));
    f[0][0 + V] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = -V; j <= V; j++)
            f[i & 1][j + V] = max(f[(i - 1) & 1][j + V], f[(i - 1) & 1][j - v[i] + V] + w[i]);
    int ans = 0;
    for (int j = 0; j <= V; j++)
        if (f[n & 1][j + V] >= 0)
            ans = max(ans, j + f[n & 1][j + V]);
    cout << ans;
    return 0;
}