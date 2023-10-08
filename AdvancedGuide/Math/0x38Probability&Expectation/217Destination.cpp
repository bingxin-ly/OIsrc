#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, in[N], deg[N];
double dis[N];
vector<pair<int, int> > g[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[v].emplace_back(u, w), in[u]++, deg[u]++;
    queue<int> q;
    q.emplace(n);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto &[v, w] : g[u]) {
            dis[v] += (dis[u] + w) / deg[v];
            if (!--in[v]) q.emplace(v);
        }
    }
    cout << fixed << setprecision(2) << dis[1];
    return 0;
}