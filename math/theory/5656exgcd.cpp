#include <bits/stdc++.h>
#define int long long
using namespace std;

int exgcd(int a, int b, int &x, int &y) {
    if (!b) return x = 1, y = 0, a;
    int d = exgcd(b, a % b, y, x);
    return y -= a / b * x, d;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    for (cin >> T; T; T--) {
        int a, b, c, x, y;
        cin >> a >> b >> c;
        if (c % __gcd(a, b)) {
            cout << "-1\n";
            continue;
        }
        int d = exgcd(a, b, x, y), p = b / d, q = a / d;
        x *= c / d, y *= c / d;
        int l = ceil((-x + 1.) / p), r = floor((y - 1.) / q);
        if (l <= r) {
            cout << r - l + 1 << ' '
                 << x + l * p << ' ' << y - r * q << ' '
                 << x + r * p << ' ' << y - l * q << '\n';
        } else {
            cout << x + l * p << ' ' << y - r * q << '\n';
        }
    }
    return 0;
}