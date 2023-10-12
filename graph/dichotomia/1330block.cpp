#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 9;
int n, m, sum[3], ans;
vector<int> g[N];

int vis[N];
queue<int> q;
bool bfs(int s) {
    vis[s] = 1, sum[1] = 1, sum[2] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (vis[v] == vis[u]) return 1;
            if (!vis[v]) {
                vis[v] = vis[u] % 2 + 1;
                sum[vis[v]]++;
                q.push(v);
            }
        }
    }
    return 0;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int u, v; m--;) {
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        if (bfs(i))
            return cout << "Impossible", 0;
        else
            ans += min(sum[1], sum[2]);
    }
    cout << ans;
    return 0;
}
