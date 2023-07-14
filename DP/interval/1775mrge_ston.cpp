#include <bits/stdc++.h>
using namespace std;

constexpr int N = 305;
int n, s[N], f[N][N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i], s[i] += s[i - 1];
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
        f[i][i] = 0;
    for (int l = 2; l <= n; l++)
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            for (int k = i; k < j; k++)
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + (s[j] - s[i - 1]));
        }
    cout << f[1][n];
    return 0;
}