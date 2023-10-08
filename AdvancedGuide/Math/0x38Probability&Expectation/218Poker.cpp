#include <bits/stdc++.h>
using namespace std;

int A, B, C, D;
bool v[15][15][15][15][5][5];
double f[15][15][15][15][5][5];

double dp(int a, int b, int c, int d, int p, int q) {
    if (v[a][b][c][d][p][q]) return f[a][b][c][d][p][q];
    v[a][b][c][d][p][q] = 1;
    double &ans = f[a][b][c][d][p][q];
    int x = a + (p == 1) + (q == 1), y = b + (p == 2) + (q == 2),
        z = c + (p == 3) + (q == 3), w = d + (p == 4) + (q == 4);
    if (x >= A && y >= B && z >= C && w >= D) return 0;
    int cnt = 54 - x - y - z - w;
    if (cnt <= 0) return ans = 1e10;
    if (a < 13) ans += dp(a + 1, b, c, d, p, q) * (13 - a) / cnt;
    if (b < 13) ans += dp(a, b + 1, c, d, p, q) * (13 - b) / cnt;
    if (c < 13) ans += dp(a, b, c + 1, d, p, q) * (13 - c) / cnt;
    if (d < 13) ans += dp(a, b, c, d + 1, p, q) * (13 - d) / cnt;
    if (!p)
        ans += min({dp(a, b, c, d, 1, q),
                    dp(a, b, c, d, 2, q),
                    dp(a, b, c, d, 3, q),
                    dp(a, b, c, d, 4, q)}) /
               cnt;

    if (!q)
        ans += min({dp(a, b, c, d, p, 1),
                    dp(a, b, c, d, p, 2),
                    dp(a, b, c, d, p, 3),
                    dp(a, b, c, d, p, 4)}) /
               cnt;

    return ++ans;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> A >> B >> C >> D;
    double ans = dp(0, 0, 0, 0, 0, 0);
    cout << fixed << setprecision(3) << (ans > 100 ? -1 : ans);
    return 0;
}