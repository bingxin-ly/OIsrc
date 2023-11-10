#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9, M = 1e9 + 7;
int n, c[N];
long long f[N][2];
vector<int> g[N];
void dp(int u) {
    f[u][c[u]] = 1;
    for (int v : g[u]) {
        dp(v);
        // Note the order of transfer
        f[u][1] = (f[u][0] * f[v][1] + f[u][1] * f[v][0] + f[u][1] * f[v][1]) % M;
        f[u][0] = (f[u][0] * f[v][0] + f[u][0] * f[v][1]) % M;
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int u = 1, p; u < n; u++) cin >> p, g[p].emplace_back(u);
    for (int i = 0; i < n; i++) cin >> c[i];
    dp(0);
    cout << f[0][1];
    return 0;
}