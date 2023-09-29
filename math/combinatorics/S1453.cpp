#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9, M = 998244353;
int pw[N], fac[N], inv[N];
int power(int a, int b) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = 1ll * res * a % M;
        a = 1ll * a * a % M;
    }
    return res;
}
int C(int n, int m) {
    return 1ll * fac[n] * inv[m] % M * inv[n - m] % M;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    pw[0] = fac[0] = inv[0] = 1;
    for (int i = 1; i <= 100000; i++)
        pw[i] = pw[i - 1] * 2 % M,
        fac[i] = 1ll * fac[i - 1] * i % M, inv[i] = power(fac[i], M - 2);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        cout << 1ll * C(n, m) * pw[n - m] % M << '\n';
    }
    return 0;
}