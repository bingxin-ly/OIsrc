#include <iostream>
#include <vector>
using namespace std;

const int N = 1009;
int T, n, c[N], d[N];
vector<pair<int, int> > t[N];
int r, dis[N][N], f[N], g[N][N];
void dfs(int u, int p) {
    for (int i = 0; i < (int)t[u].size(); i++) {
        int v = t[u][i].first, w = t[u][i].second;
        if (v == p) continue;
        dis[r][v] = dis[r][u] + w, dfs(v, u);
    }
}
void dp(int u, int p) {
    f[u] = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        g[u][i] = dis[u][i] <= d[u] ? c[i] : 0x3f3f3f3f;
    for (int i = 0; i < (int)t[u].size(); i++) {
        int v = t[u][i].first;
        if (v == p) continue;
        dp(v, u);
        for (int j = 1; j <= n; j++)
            if (g[u][j] != 0x3f3f3f3f)
                g[u][j] += min(g[v][j] - c[j], f[v]);
    }
    for (int i = 1; i <= n; i++) f[u] = min(f[u], g[u][i]);
}
signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> T; T--;) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> c[i];
        for (int i = 1; i <= n; i++) cin >> d[i];
        for (int i = 1, u, v, w; i < n; i++)
            cin >> u >> v >> w, t[u].push_back(make_pair(v, w)), t[v].push_back(make_pair(u, w));
        for (int i = 1; i <= n; i++) r = i, dfs(i, 0);
        dp(1, 0);
        cout << f[1] << '\n';
        for (int i = 1; i <= n; i++) t[i].clear();
    }
    return 0;
}