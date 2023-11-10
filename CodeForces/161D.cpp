#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e4 + 9, K = 509;
int n, k;
vector<int> g[N];

long long ans, f[N][K];
void dp(int u, int p) {
    f[u][0] = 1;
    for (int v : g[u])
        if (v != p) {
            dp(v, u);
            for (int j = 0; j < k; j++) ans += f[u][j] * f[v][k - j - 1];
            for (int j = 0; j < k; j++) f[u][j + 1] += f[v][j];
        }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int u, v; --n;)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    dp(1, 0);
    cout << ans;
    return 0;
}