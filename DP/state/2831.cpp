#include <bits/stdc++.h>
using namespace std;

constexpr int N = 20;
constexpr double eps = 1e-8;
int n, m, zrobit[1 << N], ls[N][N], f[1 << N];
double x[N], y[N];
void equa(double &x, double &y, double a1, double b1, double c1, double a2, double b2, double c2) {
    y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
    x = (c1 - b1 * y) / a1;
}
void solve() {
    memset(ls, 0, sizeof(ls)), memset(f, 0x3f, sizeof(f)), f[0] = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (abs(x[i] - x[j]) < eps) continue;
            double a, b;
            equa(a, b, x[i] * x[i], x[i], y[i], x[j] * x[j], x[j], y[j]);
            if (a > -eps) continue;
            for (int k = 1; k <= n; k++)
                if (abs(a * x[k] * x[k] + b * x[k] - y[k]) < eps) ls[i][j] |= 1 << (k - 1);
        }
    for (int i = 0; i < 1 << n; i++) {
        int j = zrobit[i];
        f[i | 1 << (j - 1)] = min(f[i | 1 << (j - 1)], f[i] + 1);
        for (int k = 1; k <= n; k++) f[i | ls[j][k]] = min(f[i | ls[j][k]], f[i] + 1);
    }
    cout << f[(1 << n) - 1] << '\n';
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (int i = 0; i < 1 << 18; i++) {
        int j = 0;
        while (j < 18 && i & 1 << j) j++;
        zrobit[i] = j + 1;
    }
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}