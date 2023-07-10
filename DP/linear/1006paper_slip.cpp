#include <bits/stdc++.h>
#define max(a, b, c, d) max(max(a, b), max(c, d))
using namespace std;

constexpr int N = 55;
int f[N][N][N][N], a[N][N];

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= n; k++)
                for (int l = 1; l <= m; l++)
                {
                    f[i][j][k][l] =
                        max(f[i - 1][j][k - 1][l],
                            f[i - 1][j][k][l - 1],
                            f[i][j - 1][k - 1][l],
                            f[i][j - 1][k][l - 1]) +
                        a[i][j] + a[k][l];
                    if (i == k && l == j)
                        f[i][j][k][l] -= a[i][j];
                }

    cout << f[n][m - 1][n - 1][m] << endl;
    return 0;
}