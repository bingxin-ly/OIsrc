#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 40;
struct frac {
    int p, q;
    frac(int x = 0, int y = 1) : p(x), q(y) {
        int d = __gcd(p, q);
        p /= d, q /= d;
    }
    friend frac operator+(frac x, frac y) {
        int q = x.q * y.q / __gcd(x.q, y.q);
        x.p *= q / x.q, y.p *= q / y.q;
        return frac(x.p + y.p, q);
    }
} f[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (int n; cin >> n;) {
        f[n] = frac();
        for (int i = n - 1; i >= 0; i--)
            f[i] = f[i + 1] + frac(n, n - i);
        int a = f[0].p / f[0].q, b = f[0].p % f[0].q, c = f[0].q;
        if (!b)
            cout << a << '\n';
        else {
            int x = to_string(a).size(), y = to_string(max(b, c)).size();
            cout << string(x, ' ') << ' ' << b << '\n'
                 << a << ' ' << string(y, '-') << '\n'
                 << string(x, ' ') << ' ' << c << '\n';
        }
    }
    return 0;
}