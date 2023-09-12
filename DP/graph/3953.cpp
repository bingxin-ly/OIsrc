#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int N = 1e5 + 5;
int n, m, k, p, ring;
vector<pii> pos[N], neg[N];

int dis[N], vis[N];
void dijkstra() {
    memset(vis, 0, sizeof(vis)), memset(dis, 0x3f, sizeof(dis));
    priority_queue<pii, vector<pii>, greater<>> q;
    q.emplace(dis[1] = 0, 1);
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (const auto &[v, w] : pos[u])
            if (dis[v] > dis[u] + w) q.emplace(dis[v] = dis[u] + w, v);
    }
}
int f[N][55], in[N][55];
int dp(int u, int k) {
    if (k < 0) return 0;
    if (in[u][k]) return ring = 1, 0;
    if (f[u][k]) return f[u][k];

    in[u][k] = 1;
    int res = 0;
    for (const auto &[v, w] : neg[u]) {
        (res += dp(v, dis[u] - dis[v] + k - w)) %= p;
        if (ring) return 0;
    }
    in[u][k] = 0;
    return f[u][k] = res;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k >> p;
        for (int i = 1, u, v, w; i <= m; i++)
            cin >> u >> v >> w, pos[u].emplace_back(v, w),
                neg[v].emplace_back(u, w);
        dijkstra();
        dp(1, 0), f[1][0] = 1;
        int ans = 0;
        for (int i = 0; i <= k; i++) (ans += dp(n, i)) %= p;
        if (ring)
            cout << "-1\n";
        else
            cout << ans << '\n';

        ring = 0, memset(f, 0, sizeof(f)), memset(in, 0, sizeof(in));
        for (int i = 1; i <= n; i++) pos[i].clear(), neg[i].clear();
    }
    return 0;
}