#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e4 + 9;
int n, m;
vector<pair<int, int> > g[N];

int vis[N];
bool dfs(int u, int col, int lim) {
    vis[u] = col;
    for (const auto &[v, w] : g[u])
        if (w > lim)
            if (!vis[v] && !dfs(v, 3 - col, lim))
                return false;
            else if (vis[v] != 3 - col)
                return false;
    return true;
}
bool ok(int lim) {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++)
        if (!vis[i] && !dfs(i, 1, lim)) return false;
    return true;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    int l = 0, r = 1e9;
    while (l < r) {
        int s = (l + r) >> 1;
        ok(s) ? r = s : l = s + 1;
    }
    cout << l;
    return 0;
}