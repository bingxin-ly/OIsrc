#include <bits/stdc++.h>
using namespace std;

constexpr int N = 55;
int n, c, loc[N], sum[N], f[N][N][2];

inline int calc(int t, int l, int r) { return t * (sum[l] + (sum[n] - sum[r - 1])); }
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> c;
    for (int i = 1; i <= n; i++)
        cin >> loc[i] >> sum[i], sum[i] += sum[i - 1];
    memset(f, 0x3f, sizeof(f));
    f[c][c][0] = f[c][c][1] = 0;
    for (int i = 2; i <= n; i++)
        for (int l = 1; l <= n - i + 1; l++)
        {
            int r = l + i - 1;
            f[l][r][0] = min(f[l + 1][r][0] + calc(loc[l + 1] - loc[l], l, r + 1),
                             f[l + 1][r][1] + calc(loc[r] - loc[l], l, r + 1));
            f[l][r][1] = min(f[l][r - 1][0] + calc(loc[r] - loc[l], l - 1, r),
                             f[l][r - 1][1] + calc(loc[r] - loc[r - 1], l - 1, r));
            // cerr << f[l][r][0] << ' ' << f[l][r][1] << endl;
        }
    cout << min(f[1][n][0], f[1][n][1]);
    return 0;
}