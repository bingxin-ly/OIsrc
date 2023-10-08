#include <bits/stdc++.h>
#define long long long
using namespace std;

long exgcd(long a, long b, long &x, long &y) {
    if (!b) return x = 1, y = 0, a;
    long d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    long n, a, b;
    cin >> n >> a >> b;
    long lcm = a, ans = b;
    while (--n) {
        cin >> a >> b;
        b = (b - ans % a + a) % a;
        long x, y, d = exgcd(lcm, a, x, y);
        if (b % d) return cout << -1, 0;

        long k = x * (b / d) % a;
        ans += k * lcm, lcm = lcm / d * a;
        ans = (ans % lcm + lcm) % lcm;
    }
    cout << ans;
    return 0;
}