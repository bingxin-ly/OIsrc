#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3009, M = 309;  // 3000 / 300
int n, m, q[N], c[M][M], f[2][M][M], px[N], py[N];
short g[N][M][M]; // 可恶 char 溢出了
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++) cin >> c[i][j];
    for (int i = 1; i <= n; i++) cin >> q[i];
    memset(f[0], 0x3f, sizeof(f[0])), f[0][1][2] = 0, q[0] = 3;
    for (int i = 1; i <= n; i++) {
        memset(f[i & 1], 0x3f, sizeof(f[i & 1]));
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= m; k++)
                if (j != k && f[i & 1 ^ 1][j][k] < 0x3f3f3f3f) {
                    int cur = f[i & 1 ^ 1][j][k];
                    if (j != q[i] && k != q[i] && f[i & 1][j][k] > cur + c[q[i - 1]][q[i]])
                        f[i & 1][j][k] = cur + c[q[i - 1]][q[i]], g[i][j][k] = 0;
                    if (q[i - 1] != q[i] && k != q[i] && f[i & 1][q[i - 1]][k] > cur + c[j][q[i]])
                        f[i & 1][q[i - 1]][k] = cur + c[j][q[i]], g[i][q[i - 1]][k] = j;
                    if (q[i - 1] != q[i] && j != q[i] && f[i & 1][j][q[i - 1]] > cur + c[k][q[i]])
                        f[i & 1][j][q[i - 1]] = cur + c[k][q[i]], g[i][j][q[i - 1]] = k;
                }
    }
    int res = 0x3f3f3f3f, rx = 0, ry = 0;
    for (int j = 1; j <= m; j++)
        for (int k = 1; k <= m; k++)
            if (j != k && res > f[n & 1][j][k])
                res = f[n & 1][j][k], rx = j, ry = k;
    cout << res << '\n', px[0] = 1, py[0] = 2;
    for (int i = n; i >= 1; i--) {
        px[i] = rx, py[i] = ry;
        int pos = g[i][rx][ry];
        if (pos) ry == q[i - 1] ? ry = pos : rx = pos;
    }
    int a = 1, b = 2;
    for (int i = 1; i <= n; i++) {
        if (px[i] == q[i - 1])
            a = 6 - a - b;
        else if (py[i] == q[i - 1])
            b = 6 - a - b;
        cout << 6 - a - b << ' ';
    }
    return 0;
}