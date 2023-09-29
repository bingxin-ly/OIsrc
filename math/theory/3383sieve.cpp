#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e8 + 9;
int m, fac[N], pri[N];
void euler(int n) {
    memset(fac, 0, sizeof(fac)), m = 0;
    for (int i = 2; i <= n; i++) {
        if (!fac[i]) fac[i] = i, pri[++m] = i;
        for (int j = 1; j <= m; j++) {
            if (pri[j] > fac[i] || pri[j] * i > n) break;
            fac[pri[j] * i] = pri[j];
        }
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, q;
    cin >> n >> q, euler(n);
    for (int k; q--;) cin >> k, cout << pri[k] << '\n';
    return 0;
}