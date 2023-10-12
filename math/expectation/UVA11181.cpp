#include <bits/stdc++.h>
using namespace std;

constexpr int N = 21;
int n, r, T;
double p[N], f[N][N];
double dp(int k) {
    for (int i = 1; i <= n; i++) {
        if (i == k)
            memcpy(f[i], f[i - 1], sizeof(f[i - 1]));
        else
            for (int j = 0; j <= i; j++) {
                f[i][j] = f[i - 1][j] * (1 - p[i]);
                if (j) f[i][j] += f[i - 1][j - 1] * p[i];
            }
    }
    return f[n][r - bool(k)];
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    f[0][0] = 1;
    while (cin >> n >> r, n || r) {
        for (int i = 1; i <= n; i++) cin >> p[i];
        double P = dp(0);
        cout << "Case " << ++T << ":\n";
        for (int i = 1; i <= n; i++)
            cout << fixed << setprecision(6) << dp(i) * p[i] / P << '\n';
    }
    return 0;
}