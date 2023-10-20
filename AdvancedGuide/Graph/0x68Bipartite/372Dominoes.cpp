#include <bits/stdc++.h>
using namespace std;

constexpr int N = 109;
int n, m, ban[N][N], dx[]{0, 0, 1, -1}, dy[]{1, -1, 0, 0};
vector<int> g[N * N];
int mch[N * N], vis[N * N];
bool dfs(int u) {
    for (int v : g[u])
        if (!vis[v]) {
            vis[v] = 1;
            if (!mch[v] || dfs(mch[v])) return mch[v] = u, true;
        }
    return false;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, ban[x][y] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (ban[i][j] || (i + j) & 1) continue;
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k], y = j + dy[k];
                if (x < 1 || y < 1 || x > n || y > n || ban[x][y]) continue;
                g[(i - 1) * n + j].emplace_back((x - 1) * n + y);
            }
        }
    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (ban[i][j] || (i + j) & 1) continue;
            memset(vis, 0, sizeof(vis));
            res += dfs((i - 1) * n + j);
        }
    cout << res;
    return 0;
}