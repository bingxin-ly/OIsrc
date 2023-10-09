#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e3 + 9;
int n, m, in[N], dis[N];
vector<tuple<int, int, int> > g[N];

void SPFA(int w) {
    queue<int> q;
    q.emplace(1), in[1] = 1;
    memset(dis, 0x3f, sizeof(dis)), dis[1] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop(), in[u] = 0;
        for (const auto &[v, c, f] : g[u])
            if (f >= w && dis[v] > dis[u] + c) {
                dis[v] = dis[u] + c;
                if (!in[v]) q.emplace(v), in[v] = 1;
            }
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int u, v, c, f; m--;)
        cin >> u >> v >> c >> f, g[u].emplace_back(v, c, f), g[v].emplace_back(u, c, f);
    double ans = 0;
    for (int i = 1; i <= 1000; i++) SPFA(i), ans = max(ans, 1. * i / dis[n]);
    cout << int(1e6 * ans);
    return 0;
}