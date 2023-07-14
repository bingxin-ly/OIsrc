#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 5, INF = 0x3f3f3f3f;
int n, a[N], f[N][3];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    memset(f[1], 0x3f, sizeof(f[1])), f[1][a[1] + 1] = 0;
    for (int i = 2; i <= n; i++)
    {
        if (a[i] == -1)
            f[i][0] = f[i - 1][0],
            f[i][1] = INF,
            f[i][2] = f[i - 1][2] + 2;
        else if (a[i] == 0)
            f[i][0] = f[i - 1][0] + 1,
            f[i][1] = min(f[i - 1][0], f[i - 1][1]),
            f[i][2] = f[i - 1][2] + 1;
        else
            f[i][0] = f[i - 1][0] + 2,
            f[i][1] = f[i - 1][0] + 1,
            f[i][2] = min(min(f[i - 1][0], f[i - 1][1]), f[i - 1][2]);
    }
    int ans = min(min(f[n][0], f[n][1]), f[n][2]);
    if (ans >= INF)
        cout << "BRAK";
    else
        cout << ans;
    return 0;
}