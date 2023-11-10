#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9, M = 998244353;
int n, f[N], g[N][63][2];
long long w[N];
vector<int> t[N];
void dp(int u, int p) {
    for (int i = 0; i < 63; i++) g[u][i][w[u] >> i & 1] = 1;
    for (int v : t[u]) {
        if (v == p) continue;
        dp(v, u);
        for (int i = 0; i < 63; i++) {
            long long g0 = g[u][i][0], g1 = g[u][i][1];
            g[u][i][0] = (g0 * (g[v][i][0] + f[v]) + g1 * g[v][i][1]) % M;
            g[u][i][1] = (g0 * g[v][i][1] + g1 * (g[v][i][0] + f[v])) % M;
        }
    }
    for (int i = 0; i < 63; i++)
        (f[u] += (1ll << i) % M * g[u][i][1] % M) %= M;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int u = 2, p; u <= n; u++)
        cin >> p, t[p].emplace_back(u), t[u].emplace_back(p);
    dp(1, 0);
    cout << f[1] << '\n';
    return 0;
}