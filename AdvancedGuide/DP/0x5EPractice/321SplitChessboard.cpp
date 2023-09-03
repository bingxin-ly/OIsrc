#include <bits/stdc++.h>
using namespace std;

constexpr int N = 10;
int n, w[N][N];
long long f[N][N][N][N][15];
long long sqr(long long $) { return $ * $; }
int sum(int u, int d, int l, int r) {
    return w[d][r] - w[d][l - 1] - w[u - 1][r] + w[u - 1][l - 1];
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++)
            cin >> w[i][j],
                w[i][j] += w[i - 1][j] + w[i][j - 1] - w[i - 1][j - 1];
    memset(f, 0x3f, sizeof(f));
    for (int row = 1; row <= 8; row++)
        for (int col = 1; col <= 8; col++)
            for (int u = 1; u <= 8 - row + 1; u++)
                for (int l = 1; l <= 8 - col + 1; l++) {
                    int d = u + row - 1, r = l + col - 1;
                    f[u][d][l][r][1] = sqr(n * sum(u, d, l, r) - w[8][8]);
                    for (int c = 2; c <= n; c++) {
                        for (int k = u; k < d; k++) {
                            f[u][d][l][r][c] = min(f[u][d][l][r][c],
                                min(f[u][k][l][r][1] + f[k + 1][d][l][r][c - 1],
                                    f[u][k][l][r][c - 1] + f[k + 1][d][l][r][1]));
                        }
                        for (int k = l; k < r; k++) {
                            f[u][d][l][r][c] = min(
                                min(f[u][d][l][k][1] + f[u][d][k + 1][r][c - 1],
                                    f[u][d][l][k][c - 1] +
                                        f[u][d][k + 1][r][1]),
                                f[u][d][l][r][c]);
                        }
                    }
                }
    cout << fixed << setprecision(3)
         << sqrt(f[1][8][1][8][n] * 1.0 / n / n / n);
    return 0;
}