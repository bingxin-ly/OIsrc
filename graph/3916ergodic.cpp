#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, a[N];
vector<int> g[N];

void dfs(int u, int p) {
    if (a[u]) return;
    a[u] = p;
    for (int v : g[u]) dfs(v, p);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int u, v; m; m--) cin >> u >> v, g[v].emplace_back(u);
    for (int i = n; i; i--) dfs(i, i);
    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    return 0;
}