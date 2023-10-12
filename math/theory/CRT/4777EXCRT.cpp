#include <bits/stdc++.h>
#define int long long
using namespace std;

int exgcd(int a, int b, int &x, int &y) {
    if (!b) return x = 1, y = 0, a;
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, a, b;
    cin >> n >> a >> b;
    int lcm = a, ans = b;
    while (--n) {
        cin >> a >> b;
        b = (b - ans % a + a) % a;
        int x, y, d = exgcd(lcm, a, x, y);
        if (b % d) return cout << -1, 0;

        int k = (__int128)x * (b / d) % a;
        ans += k * lcm, lcm = lcm / d * a;
        ans = (ans % lcm + lcm) % lcm;
    }
    cout << ans;
    return 0;
}