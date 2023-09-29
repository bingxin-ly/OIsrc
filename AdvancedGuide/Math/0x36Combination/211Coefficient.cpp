#include <bits/stdc++.h>
using namespace std;

int a, b, k, n, m, MOD = 10007;
int power(int a, int b, int p = MOD) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = 1ll * res * a % p;
        a = 1ll * a * a % p;
    }
    return res;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> a >> b >> k >> n >> m;
    int fac = 1, inv = 1;
    for (int i = k - n + 1; i <= k; i++) fac = 1ll * fac * i % MOD;
    for (int i = 1; i <= n; i++) inv = 1ll * inv * i % MOD;
    inv = power(inv, MOD - 2);
    cout << 1ll * fac * inv % MOD * power(a, n) % MOD * power(b, m) % MOD;
    return 0;
}