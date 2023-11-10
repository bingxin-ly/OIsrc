#include <bits/stdc++.h>
using namespace std;

constexpr int N = 101, K = 51;
int n, k, s[N], dep[N];
vector<pair<int, int> > t[N];

long long f[N][N][K], g[N][N][K];
vector<int> anc;
void dp(int u) {
    anc.emplace_back(u);
    for (const auto &[v, w] : t[u]) {
        dep[v] = dep[u] + w, dp(v);
        for (int j : anc)
            for (int k = ::k; k >= 0; k--) {
                f[u][j][k] += f[v][j][0], g[u][j][k] += f[v][u][0];
                for (int l = 0; l <= k; l++) {
                    f[u][j][k] = min(f[u][j][k], f[u][j][k - l] + f[v][j][l]);
                    g[u][j][k] = min(g[u][j][k], g[u][j][k - l] + f[v][u][l]);
                }
            }
    }
    for (int j : anc) {
        f[u][j][0] += s[u] * (dep[u] - dep[j]);
        for (int k = 1; k <= ::k; k++)
            f[u][j][k] = min(f[u][j][k] + s[u] * (dep[u] - dep[j]), g[u][j][k - 1]);
    }
    anc.pop_back();
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int v = 1, u, w; v <= n; v++)
        cin >> s[v] >> u >> w, t[u].emplace_back(v, w);
    dp(0);
    cout << f[0][0][k];
    return 0;
}