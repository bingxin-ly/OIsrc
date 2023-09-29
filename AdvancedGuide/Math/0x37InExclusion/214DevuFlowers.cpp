#include <bits/stdc++.h>
using namespace std;

constexpr int N = 22, MOD = 1e9 + 7;
int n, inv[N];
long long m, a[N];
int power(int a, int b) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = 1ll * res * a % MOD;
        a = 1ll * a * a % MOD;
    }
    return res;
}
int C(long long n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    long long ans = 1;
    n %= MOD;
    for (int i = 0; i < m; i++) ans = ans * (n - i) % MOD;
    for (int i = 1; i <= m; i++) ans = ans * inv[i] % MOD;
    return ans;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) inv[i] = power(i, MOD - 2);
    for (int i = 1; i <= n; i++) cin >> a[i];
    long long ans = C(n + m - 1, n - 1);
    for (int i = 1; i < 1 << n; i++) {
        long long t = n + m, c = 0;
        for (int j = 0; j < n; j++)
            if (i >> j & 1) c += 1, t -= a[j + 1];
        t -= c + 1;
        (ans += (c & 1 ? -1 : 1) * C(t, n - 1)) %= MOD;
    }
    cout << (ans + MOD) % MOD;
    return 0;
}