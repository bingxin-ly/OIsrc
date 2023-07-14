#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e4 + 5;
int n, L[N], R[N], f[N][2];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> L[i] >> R[i];
    memset(f, 0x3f, sizeof(f));
    f[1][0] = R[1] - 1 + R[1] - L[1], f[1][1] = R[1] - 1;
    for (int i = 2; i <= n; i++)
    {
        int dis = R[i] - L[i] + 1;
        f[i][0] = min(dis + abs(L[i - 1] - R[i]) + f[i - 1][0],
                      dis + abs(R[i - 1] - R[i]) + f[i - 1][1]);
        f[i][1] = min(dis + abs(L[i - 1] - L[i]) + f[i - 1][0],
                      dis + abs(R[i - 1] - L[i]) + f[i - 1][1]);
    }
    cout << min(f[n][0] + (n - L[n]), f[n][1] + (n - R[n]));
    return 0;
}