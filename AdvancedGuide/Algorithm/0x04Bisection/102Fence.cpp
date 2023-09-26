#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, f, a[N];
double b[N], c[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> f;
    for (int i = 1; i <= n; i++) cin >> a[i];

    double l = 0, r = 2000;
    while (r - l > 1e-5) {
        double mid = (l + r) / 2;
        for (int i = 1; i <= n; i++)
            b[i] = a[i] - mid, c[i] = c[i - 1] + b[i];
        double ans = -1e4, minn = 1e4;
        for (int i = f; i <= n; i++)
            minn = min(minn, c[i - f]), ans = max(ans, c[i] - minn);
        ans >= 0 ? (l = mid) : (r = mid);
    }
    cout << int(r * 1000);  // 因为下整, 宁愿取更大的 r, 也不能取更小的 l, 否则直接精度丢失
    return 0;
}