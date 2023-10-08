#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e7 + 9;
int n, v[N];
long long phi[N];
vector<int> pri;
void euler() {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!v[i]) v[i] = i, phi[i] = i - 1, pri.emplace_back(i);
        for (int p : pri) {
            if (p > v[i] || p > n / i) break;
            v[i * p] = p, phi[i * p] = phi[i] * (i % p ? p - 1 : p);
        }
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n, euler();
    for (int i = 1; i <= n; i++) phi[i] += phi[i - 1];
    long long ans = 0;
    for (int p : pri) ans += 2 * phi[n / p] - 1;
    cout << ans;
    return 0;
}