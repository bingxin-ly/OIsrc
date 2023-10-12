#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, dep[N];
vector<int> g[N];
void dfs(int u, int p) {
    dep[u] = dep[p] + 1;
    for (int v : g[u])
        if (v != p) dfs(v, u);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    dfs(1, 0);
    double ans = 0;
    for (int i = 1; i <= n; i++) ans += 1. / dep[i];
    cout << fixed << setprecision(8) << ans;
    return 0;
}