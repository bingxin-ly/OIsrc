#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, siz[N];
vector<pair<int, int> > g[N];
long long ans;
void dfs(int u, int p) {
    siz[u] = 1;
    for (const auto &[v, w] : g[u])
        if (v != p) {
            dfs(v, u), siz[u] += siz[v];
            ans += 1ll * w * abs(2 * siz[v] - n);
        }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    dfs(1, 0);
    cout << ans;
    return 0;
}