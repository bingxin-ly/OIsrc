#include <bits/stdc++.h>
using namespace std;

double a, b, c, d, eps = 1e-6;
double calc(double x) { return a * x * x * x + b * x * x + c * x + d; }
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> a >> b >> c >> d;
    for (int i = -100; i < 100; i++) {
        double l = i, r = i + 1 - eps;
        if (calc(l) * calc(r) > eps)
            continue;
        while (r - l > eps) {
            double m = (l + r) / 2;
            calc(m) * calc(r) < eps ? l = m : r = m;
        }
        cout << fixed << setprecision(2) << l << ' ';
    }
    return 0;
}