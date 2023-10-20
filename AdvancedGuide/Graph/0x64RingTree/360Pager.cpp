#include <bits/stdc++.h>
using namespace std;

constexpr int M = 1.2e4 + 9;
int n, m, q, idx = 1, hed[M], nxt[M << 2], ver[M << 2], val[M << 2];
void link(int u, int v, int w) {
    ver[++idx] = v, val[idx] = w, nxt[idx] = hed[u], hed[u] = idx;
}
int dis[M], vis[M];
void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > q;
    memset(dis, 0x3f, sizeof(dis)), q.emplace(dis[1] = 0, 1);
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = hed[u]; i; i = nxt[i]) {
            int v = ver[i], w = val[i];
            if (dis[v] > dis[u] + w)
                q.emplace(dis[v] = dis[u] + w, v);
        }
    }
}
int tim, dfn[M], frm[M], cnt, inc[M], sum[M], len[M], brk[M << 2];
void cycle(int u, int v, int i) {
    cnt += 1;
    sum[v] = val[i], brk[i] = brk[i ^ 1] = 1;
    while (v != u) {
        inc[v] = cnt;
        int vv = ver[frm[v] ^ 1];
        sum[vv] = sum[v] + val[frm[v]], brk[frm[v]] = brk[frm[v] ^ 1] = 1;
        link(u, v, dis[v] - dis[u]), link(v, u, dis[v] - dis[u]);
        v = vv;
    }
    inc[v] = cnt, len[cnt] = sum[v];
}
void dfs1(int u) {
    dfn[u] = ++tim;
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = ver[i];
        if (!dfn[v])
            frm[v] = i, dfs1(v);
        else if ((i ^ 1) != frm[u] && dfn[v] >= dfn[u])
            cycle(u, v, i);
    }
}
int f[M][14], d[M];
void dfs2(int u, int p) {
    f[u][0] = p, d[u] = d[p] + 1;
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = ver[i];
        if (!d[v] && !brk[i]) dfs2(v, u);
    }
}
int calc(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    int ou = u, ov = v;
    for (int i = __lg(n); i >= 0; i--)
        if (d[f[u][i]] >= d[v]) u = f[u][i];
    if (u == v) return dis[ou] - dis[ov];
    for (int i = __lg(n); i >= 0; i--)
        if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    if (!inc[u] || inc[u] != inc[v]) return dis[ou] + dis[ov] - 2 * dis[f[u][0]];
    int l = abs(sum[v] - sum[u]);
    return dis[ou] - dis[u] + dis[ov] - dis[v] + min(l, len[inc[u]] - l);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, link(u, v, w), link(v, u, w);
    dijkstra(), dfs1(1), dfs2(1, 0);
    for (int i = 1; i <= __lg(n); i++)
        for (int u = 1; u <= n; u++) f[u][i] = f[f[u][i - 1]][i - 1];

    for (int u, v; q--;) {
        cin >> u >> v;
        cout << calc(u, v) << '\n';
    }
    return 0;
}