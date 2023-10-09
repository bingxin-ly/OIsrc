#include <bits/stdc++.h>
using namespace std;

constexpr int N = 109;
int n;
double a[N][N], b[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> a[i][j];
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++)
            if (fabs(a[j][i]) > 1e-8) {
                swap(a[i], a[j]), swap(b[i], b[j]);
                break;
            }
        if (fabs(a[i][i]) < 1e-8) return cout << "No Solution", 0;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            double r = a[j][i] / a[i][i];
            for (int k = i; k <= n; k++) a[j][k] -= a[i][k] * r;
            b[j] -= b[i] * r;
        }
    }
    for (int i = 1; i <= n; i++)
        cout << fixed << setprecision(2) << b[i] / a[i][i] + 1e-8 << '\n';
    return 0;
}