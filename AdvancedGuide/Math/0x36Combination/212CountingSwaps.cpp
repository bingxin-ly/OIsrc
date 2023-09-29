#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9, MOD = 1e9 + 9;
int n, p[N], v[N], fac[N];
int power(int a, int b) {
    if (b < 0) return 1;
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = 1ll * res * a % MOD;
        a = 1ll * a * a % MOD;
    }
    return res;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    fac[0] = 1;
    for (int i = 1; i <= 100000; i++) fac[i] = 1ll * fac[i - 1] * i % MOD;
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> p[i];
        memset(v, 0, sizeof(v));
        int cnt = 0, ans = 1;
        for (int i = 1; i <= n; i++) {
            if (v[i]) continue;
            int j = i, l = 0;
            do {
                l += 1, v[j] = 1, j = p[j];
            } while (j != i);
            cnt += 1;
            ans = 1ll * ans * power(l, l - 2) % MOD;
            ans = 1ll * ans * power(fac[l - 1], MOD - 2) % MOD;
        }
        ans = 1ll * ans * fac[n - cnt] % MOD;
        cout << ans << '\n';
    }
    return 0;
}