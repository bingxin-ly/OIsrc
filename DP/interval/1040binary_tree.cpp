#include <bits/stdc++.h>
using namespace std;

constexpr int N = 30;
unsigned n, f[N][N], rt[N][N];

void print(int l, int r)
{
    if (l > r)
        return;
    cout << rt[l][r] << ' ';
    print(l, rt[l][r] - 1);
    print(rt[l][r] + 1, r);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (unsigned i = 1; i <= n; i++)
        cin >> f[i][i], rt[i][i] = i, f[i][i - 1] = 1; // 处理越界的情况~
    for (unsigned l = 2; l <= n; l++)
        for (unsigned i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            for (int k = i; k < j; k++)
                if (f[i][k - 1] * f[k + 1][j] + f[k][k] > f[i][j])
                    f[i][j] = f[i][k - 1] * f[k + 1][j] + f[k][k], rt[i][j] = k;
        }
    cout << f[1][n] << '\n';
    print(1, n);
    return 0;
}