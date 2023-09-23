#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;
int T, n, m, k;
long long power(int a, int b) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = 1ll * res * a % MOD;
        a = 1ll * a * a % MOD;
    }
    return res;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        long long ans = 0;
        for (int i = 1; i <= k; i++)
            (ans += (power(i, n) - power(i - 1, n)) * ((power(i, m)) - power(i - 1, m))) %= MOD;
        cout << (ans + MOD) % MOD << '\n';
    }
    return 0;
}
