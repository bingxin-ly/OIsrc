#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 1e5 + 9;
int T, n, m, p, fac[N];
int pow(int a, int b, int p) {
    int r = 1;
    for (; b; b >>= 1) {
        if (b & 1) r = 1ll * r * a % p;
        a = 1ll * a * a % p;
    }
    return r;
}
int C(int n, int m, int p) {
    return n >= m ? fac[n] * pow(fac[m], p - 2, p) * pow(fac[n - m], p - 2, p) % p : 0;
}
int lucas(int n, int m, int p) {
    return m ? C(n % p, m % p, p) * lucas(n / p, m / p, p) % p : 1;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    fac[0] = 1;
    for (cin >> T; T; T--) {
        cin >> n >> m >> p;
        for (int i = 1; i < p; i++) fac[i] = fac[i - 1] * i % p;
        cout << lucas(n + m, m, p) << '\n';
    }
    return 0;
}