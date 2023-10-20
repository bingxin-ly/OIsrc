#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, s;
int idx = 1, hed[N], nxt[N << 1], ver[N << 1], len[N << 1];
void link(int u, int v, int w) {
    ver[++idx] = v, len[idx] = w, nxt[idx] = hed[u], hed[u] = idx;
}
int dep[N], pre[N];
int bfs(int s) {
    memset(dep, -1, sizeof(dep));
    queue<int> q;
    q.emplace(s), dep[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = hed[u]; i; i = nxt[i]) {
            int v = ver[i], w = len[i];
            if (dep[v] == -1)
                dep[v] = dep[u] + w, pre[v] = i, q.emplace(v);
        }
    }
    return max_element(dep + 1, dep + n + 1) - dep;
}
int a[N], b[N], vis[N], dis[N], sum[N];
void dfs(int u) {
    vis[u] = 1;
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = ver[i], w = len[i];
        if (vis[v]) continue;
        dfs(v), dis[u] = max(dis[u], dis[v] + w);
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> s;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, link(u, v, w), link(v, u, w);
    int p = bfs(1), q = bfs(p), t = 0;
    while (q != p) {
        a[++t] = q, b[t + 1] = len[pre[q]];
        q = ver[pre[q] ^ 1];
    }
    a[++t] = q;
    for (int i = 1; i <= t; i++) vis[a[i]] = 1;
    int mxv = 0;
    for (int i = 1; i <= t; i++) {
        dfs(a[i]);
        mxv = max(mxv, dis[a[i]]), sum[i] = sum[i - 1] + b[i];
    }
    int ans = 1 << 30;
    for (int i = 1, j = 1; i <= t; i++) {
        while (j < t && sum[j + 1] - sum[i] <= s) j++;
        ans = min(ans, max(mxv, max(sum[i], sum[t] - sum[j])));
    }
    cout << ans;
    return 0;
}