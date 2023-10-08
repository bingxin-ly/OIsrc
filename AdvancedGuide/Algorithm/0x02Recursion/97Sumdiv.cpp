#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 9901;
int power(int a, int b, int p = MOD) {
    int res = 1;
    for (a %= p; b; b >>= 1) {
        if (b & 1) res = 1ll * res * a % p;
        a = 1ll * a * a % p;
    }
    return res;
}
// 使用分治法求 sum(p, c) = p^0 + p^1 + p^2 + ... + p^c
int sum(int p, int c) {
    if (!c)
        return 1;
    if (c & 1)
        return (1 + power(p, (c + 1) >> 1)) * sum(p, (c - 1) >> 1) % MOD;
    else
        return ((1 + power(p, c >> 1)) * sum(p, (c >> 1) - 1) + power(p, c)) % MOD;
}
signed main() {
    int a, b;
    cin >> a >> b;
    if (!a) return cout << 0, 0;
    int res = 1;
    for (int p = 2, u = sqrt(a); p <= u; p++)
        if (a % p == 0) {
            int c = 0;
            while (a % p == 0) c += 1, a /= p;
            (res *= sum(p, b * c)) %= MOD;
        }
    if (a != 1) (res *= sum(a, b)) %= MOD;
    cout << res;
    return 0;
}