#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 9;
int n, m, s, t;
vector<int> pos[N], neg[N];

int col[N], vad[N], dis[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        if (u != v) pos[u].emplace_back(v), neg[v].emplace_back(u);
    }
    cin >> s >> t;

    queue<int> q;
    q.emplace(t), col[t] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : neg[u])
            if (!col[v]) col[v] = 1, q.emplace(v);
    }

    for (int u = 1; u <= n; u++) {
        vad[u] = col[u];
        for (int v : pos[u]) vad[u] &= col[v];
    }
    if (!col[s] || !vad[s]) return cout << -1, 0;

    q.emplace(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == t) break;
        for (int v : pos[u])
            if (vad[v] && !dis[v]) dis[v] = dis[u] + 1, q.emplace(v);
    }
    cout << dis[t];
    return 0;
}