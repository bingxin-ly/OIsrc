#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int n, m, a[N][N];
int f[N][N], c[N][N];

void print(int i, int j)
{
    if (!i)
        return;
    print(i - 1, c[i][j]);
    cout << j << ' ';
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= m; j++)
        {
            f[i][j] = ~0x3f3f3f3f;
            for (int k = i - 1; k < j; k++)
                if (f[i - 1][k] > f[i][j])
                    f[i][j] = f[i - 1][k], c[i][j] = k;
            f[i][j] += a[i][j];
        }
    int ans = ~0x3f3f3f3f, tail = 0;
    for (int j = n; j <= m; j++)
        if (f[n][j] > ans)
            ans = f[n][j], tail = j;
    cout << ans << '\n';
    print(n, tail);
    return 0;
}