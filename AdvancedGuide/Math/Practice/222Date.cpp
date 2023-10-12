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
    int a, b, m, n, l, x, y;
    cin >> a >> b >> m >> n >> l;
    int d = exgcd(m - n, l, x, y), k;
    if ((b - a) % d) return cout << "Impossible", 0;
    x *= (b - a) / d, k = abs(l / d);
    cout << (x % k + k) % k;
    return 0;
}