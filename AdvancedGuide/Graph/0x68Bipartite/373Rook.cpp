#include <bits/stdc++.h>
using namespace std;

constexpr int N = 209;
int n, m, t, ban[N][N];
int mch[N], vis[N];
bool dfs(int x) {
    for (int y = 1; y <= m; y++) {
        if (vis[y] || ban[x][y]) continue;
        vis[y] = 1;
        if (!mch[y] || dfs(mch[y])) return mch[y] = x, true;
    }
    return false;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> t;
    for (int i = 1, x, y; i <= t; i++) cin >> x >> y, ban[x][y] = 1;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        res += dfs(i);
    }
    cout << res;
    return 0;
}