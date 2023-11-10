#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 9, M = 998244353;
int n, m, fac[N], inv[N], ifac[N], ans[N], sum;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        fac[i] = 1ll * fac[i - 1] * i % M;
        inv[i] = 1ll * (M - M / i) * inv[M % i] % M;
        ifac[i] = 1ll * ifac[i - 1] * inv[i] % M;
    }
    m = (n + 1) >> 1;
    for (int i = n - m + 1; i; i--) {
        ans[i] = (1ll * fac[n - i] * fac[n - m] % M * ifac[n - i - m + 1] - 1ll * inv[i] * sum) % M;
        (sum += ans[i]) %= M;
    }
    for (int i = 1; i <= n; i++) cout << (ans[i] + M) % M << ' ';
    return 0;
}