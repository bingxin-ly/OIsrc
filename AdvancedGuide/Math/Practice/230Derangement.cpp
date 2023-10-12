#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9, M = 1e9 + 7;
int T, n, m, F[N], D[N];
int pow(int a, int b) {
    int r = 1;
    for (/* a %= p, b %= φ(p) */; b; b >>= 1) {
        if (b & 1) r = 1ll * r * a % M;
        a = 1ll * a * a % M;
    }
    return r;
}
int C(int n, int m) {
    return 1ll * F[n] * pow(F[m], M - 2) % M * pow(F[n - m], M - 2) % M;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    F[0] = 1;
    for (int i = 1; i <= 1000000; i++)
        F[i] = 1ll * F[i - 1] * i % M;
    D[0] = 1, D[1] = 0;
    for (int i = 2; i <= 1000000; i++)
        D[i] = (1ll * i * D[i - 1] % M + (i & 1 ? -1 : 1)) % M;
    for (cin >> T; T--;) {
        cin >> n >> m;
        cout << 1ll * C(n, m) * D[n - m] % M << '\n';
    }
    return 0;
}