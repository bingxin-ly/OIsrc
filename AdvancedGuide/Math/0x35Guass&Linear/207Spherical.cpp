#include <bits/stdc++.h>
using namespace std;

constexpr int N = 12;
int n;
double a[N][N], b[N][N], c[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            b[i][j] = 2 * (a[i][j] - a[i + 1][j]);
            c[i] += a[i][j] * a[i][j] - a[i + 1][j] * a[i + 1][j];
        }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++)
            if (fabs(b[j][i]) > 1e-8) {
                swap(b[i], b[j]), swap(c[i], c[j]);
                break;
            }
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            double r = b[j][i] / b[i][i];
            for (int k = i; k <= n; k++) b[j][k] -= b[i][k] * r;
            c[j] -= c[i] * r;
        }
    }
    for (int i = 1; i <= n; i++)
        cout << fixed << setprecision(3) << c[i] / b[i][i] + 1e-8 << ' ';  // 不处理会被卡
    return 0;
}