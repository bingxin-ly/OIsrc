#include <bits/stdc++.h>
using namespace std;

constexpr int N = 51;
int n, q;
char s[N];
double p, f[N][N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> p >> q >> (s + 1), p /= 100;
    if (n > 50) return cout << "1.000", 0;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++) {
            if (s[i] == '1') {
                f[i][j] += f[i - 1][j] * (1 - p);
                if (j) f[i][j] += f[i - 1][j - 1] * p;
            }
            else {
                f[i][j] += f[i - 1][j] * p;
                if (j) f[i][j] += f[i - 1][j - 1] * (1 - p);
            }
        }
    double ans = 0;
    for (int j = q; j <= n; j++) ans += f[n][j];
    cout << fixed << setprecision(3) << ans;
    return 0;
}