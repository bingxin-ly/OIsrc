#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005, offset = 5000;
int f[2][12005];
signed main()
{
    int n;
    cin >> n;
    memset(f, 0x3f, sizeof(f));
    f[0][0 + offset] = 0;
    for (int i = 1, a, b, d; i <= n; i++)
    {
        cin >> a >> b, d = a - b;
        for (int j = -5000; j <= 5000; j++)
            f[i & 1][j + offset] = min(f[(i - 1) & 1][j - d + offset], f[(i - 1) & 1][j + d + offset] + 1);
    }
    for (int j = 0; j <= 5000; j++)
    {
        int ans = min(f[n & 1][j + offset], f[n & 1][-j + offset]);
        if (ans != 0x3f3f3f3f)
            cout << ans, exit(0);
    }
    return 0;
}