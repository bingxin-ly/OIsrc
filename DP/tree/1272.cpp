#include <bits/stdc++.h>
using namespace std;

constexpr int N = 151;
int n, p, f[N][N];
vector<int> g[N];
void dp(int u, int r) {
    f[u][1] = g[u].size();
    for (int v : g[u]) {
        if (v == r) continue;
        dp(v, u);
        for (int j = p; j >= 1; j--)
            for (int k = 1; k < j; k++)
                f[u][j] = min(f[u][j], f[u][k] + f[v][j - k] - 2);
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> p;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    memset(f, 0x3f, sizeof(f)), dp(1, 0);
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) ans = min(ans, f[i][p]);
    cout << ans;
    return 0;
}