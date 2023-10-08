#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, a[N], b[N];
double ansxor, ansand, ansor;

void rainbow(int k) {
    int c1 = 0, c2 = 0, pr[] = {0, 0};
    double w = 1. * (1 << k) / n / n;
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] >> k & 1;
        if (b[i]) ansxor += w, ansand += w, ansor += w;
        if (!b[i])
            ansor += 2 * w * pr[1];
        else
            ansor += 2 * w * (i - 1), ansand += 2 * w * (i - 1 - pr[0]);
        ansxor += 2 * w * (b[i] ? c1 : c2), c1 += 1;
        if (b[i]) swap(c1, c2);
        pr[b[i]] = i;
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < 31; i++) rainbow(i);
    cout << fixed << setprecision(3) << ansxor << ' ' << ansand << ' ' << ansor;
    return 0;
}