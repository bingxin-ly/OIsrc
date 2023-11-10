#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 9, M = 998244353;
int T, n, m, k, fac[N], inv[N];
int pow(int a, int b) {
    int r = 1;
    for (/* a %= p, b %= φ(p) */; b; b >>= 1) {
        if (b & 1) r = 1ll * r * a % M;
        a = 1ll * a * a % M;
    }
    return r;
}
int C(int n, int m) { return 1ll * fac[n] * inv[m] % M * inv[n - m] % M; }
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= 2e5; i++)
        fac[i] = 1ll * fac[i - 1] * i % M, inv[i] = pow(fac[i], M - 2);
    for (cin >> T; T--;) {
        cin >> n >> m >> k;
        int nn = min(n, k), mm = min(m, k), an = 0, am = 0, bn = 0, bm = 0;
        for (int i = nn % 2; i <= nn; i += 2) (an += C(n, i)) %= M;
        for (int i = mm % 2; i <= mm; i += 2) (am += C(m, i)) %= M;
        if (!(n % 2) && !(m % 2)) {
            int l = max(n - k, 0), r = min(n, k);
            for (int i = l; i <= r; i += 2) (bn += C(n, i)) %= M;
            l = max(m - k, 0), r = min(m, k);
            for (int i = l; i <= r; i += 2) (bm += C(m, i)) %= M;
        }
        cout << (1ll * an * am % M - 1ll * bn * bm % M * inv[2] % M + M) % M << '\n';
    }
    return 0;
}