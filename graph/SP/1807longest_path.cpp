#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1509, M = 5e4 + 9;
int n, m, in[N], f[N];
vector<pair<int, int> > g[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int u, v, w; m--;)
        cin >> u >> v >> w, g[u].emplace_back(v, w), in[v]++;
    fill(f + 2, f + n + 1, INT_MIN);
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i]) q.emplace(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto &[v, w] : g[u]) {
            f[v] = max(f[v], f[u] + w);
            if (!--in[v]) q.emplace(v);
        }
    }
    cout << (f[n] != INT_MIN ? f[n] : -1);
    return 0;
}