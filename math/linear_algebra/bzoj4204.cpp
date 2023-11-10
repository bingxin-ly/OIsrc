#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1009;
int n, m, k, s[N];
double a[N], b[N];
void mul(double a[], double b[]) {
    double c[N]{};
    for (int j = 1; j <= n; j++)
        for (int k = 1; k <= n; k++)
            c[j] += a[k] * b[(j - k + n) % n + 1];
    memcpy(a, c, sizeof(c));
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> s[i];
    a[1] = (m - 1.) / m, a[n] = 1. / m, b[1] = 1.;

    for (; k; k >>= 1) {
        if (k & 1) mul(b, a);
        mul(a, a);
    }
    for (int i = 1; i <= n; i++) {
        double ans = 0;
        for (int j = 1; j <= n; j++) ans += b[(j - i + n) % n + 1] * s[j];
        cout << fixed << setprecision(3) << ans << '\n';
    }
    return 0;
}