#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    long long n, k, ans;
    cin >> n >> k, ans = n * k;
    for (int x = 1, gx; x <= n; x = gx + 1) {
        gx = k / x ? min(k / (k / x), n) : n;
        ans -= (k / x) * (x + gx) * (gx - x + 1) / 2;
    }
    cout << ans;
    return 0;
}