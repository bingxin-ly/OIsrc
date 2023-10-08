#include <bits/stdc++.h>
#define int long long
using namespace std;

long long mul(long long a, long long b, long long p) {
    long long res = 0;
    for (; b; b >>= 1) {
        if (b & 1) res = (res + a) % p;
        a = (a + a) % p;
    }
    return res;
}
int pow(int a, int b, int p) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = mul(res, a, p);
        a = mul(a, a, p);
    }
    return res;
}
int phi(int n) {
    int ans = n;
    for (int i = 2, j = sqrt(n); i <= j; i++)
        if (!(n % i)) {
            ans = ans / i * (i - 1);
            while (!(n % i)) n /= i;
        }
    if (n != 1) ans = ans / n * (n - 1);
    return ans;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int l, c = 0;
    while (cin >> l, l) {
        int o = 9 * l / __gcd(l, 8ll), p = phi(o);
        set<int> d;
        for (int i = 1, j = sqrt(p); i <= j; i++)
            if (!(p % i)) d.emplace(i), d.emplace(p / i);
        bool ok = 0;
        for (int i : d)
            if (pow(10, i, o) == 1) {
                ok = 1, cout << "Case " << ++c << ": " << i << "\n";
                break;
            }
        if (!ok) cout << "Case " << ++c << ": 0\n";
    }
    return 0;
}