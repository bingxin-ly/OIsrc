#include <bits/stdc++.h>
#define long long long
using namespace std;

long squ(long $) { return $ * $; }
pair<long, long> calc(int n, long m) {
    if (!n)
        return {0, 0};
    auto len = 1ll << (n - 1), cnt = 1ll << ((n - 1) << 1);
    auto [x, y] = calc(n - 1, m % cnt);
    switch (m / cnt) {
        case 0:
            return {y, x};
        case 1:
            return {x, y + len};
        case 2:
            return {x + len, y + len};
        case 3:
            return {2 * len - y - 1, len - x - 1};
    }
}

signed main() {
    int n;
    cin >> n;
    while (n--) {
        long n, a, b;
        cin >> n >> a >> b;
        auto [ax, ay] = calc(n, a - 1);
        auto [bx, by] = calc(n, b - 1);
        cout << fixed << setprecision(0)
             << sqrt(squ(ax - bx) + squ(ay - by)) * 10 << '\n';
    }
    return 0;
}