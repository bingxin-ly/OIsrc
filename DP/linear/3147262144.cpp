#include <bits/stdc++.h>
using namespace std;

int n, ans, f[60][270000];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, x; i <= n; i++)
        cin >> x, f[x][i] = i + 1;
    for (int i = 2; i <= 58; i++)
        for (int j = 1; j <= n; j++)
        {
            if (!f[i][j])
                f[i][j] = f[i - 1][f[i - 1][j]];
            if (f[i][j])
                ans = i;
        }
    cout << ans;
    return 0;
}