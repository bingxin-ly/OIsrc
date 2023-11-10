#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, val[N], siz[N];
vector<int> g[N], f[N];

void dp(int u) {
    siz[u] = 1, f[u][1] = val[u];
    for (int v : g[u]) {
        dp(v), siz[u] += siz[v];
        for (int j = min(m, siz[u]); j > 0; j--)
            for (int k = 0; k <= min(siz[v], j - 1); k++)
                f[u][j] = max(f[u][j], f[u][j - k] + f[v][k]);
    }
}
int main() {
    cin >> n >> m, m += 1;
    for (int i = 0; i <= n; i++) f[i].resize(m + 1);
    for (int v = 1, u; v <= n; v++) {
        cin >> u >> val[v];
        g[u].emplace_back(v);
    }
    dp(0);
    cout << f[0][m];
    return 0;
}
