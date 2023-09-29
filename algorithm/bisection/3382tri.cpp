#include <bits/stdc++.h>
using namespace std;

constexpr int N = 14;
int n;
double k[N];
double calc(double x) {
    double y = 0, xx = 1;
    for (int i = 0; i <= n; i++) y += k[i] * xx, xx *= x;
    return y;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    double l, r, eps = 1e-8;
    cin >> n >> l >> r;
    for (int i = n; i >= 0; i--) cin >> k[i];
    while (r - l > eps) {
        double c = (r - l) / 3, a = l + c, b = r - c;
        double ya = calc(a), yb = calc(b);
        ya > yb ? r = b : l = a;
    }
    cout << fixed << setprecision(5) << l;
    return 0;
}