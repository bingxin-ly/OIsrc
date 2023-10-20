#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9, M = 3e5 + 9;
int n, m, v[M];
struct {
    int u, v, w;
} e[M];
vector<pair<int, int> > t[N];
int p[N], d[N], f[N][18], g[N][18][2];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
void dfs(int u, int p) {
    f[u][0] = p, d[u] = d[p] + 1;
    for (const auto &[v, w] : t[u])
        if (v != p) g[v][0][0] = w, g[v][0][1] = -1, dfs(v, u);
}
void upd(int c[], int a[], int b[]) {
    c[1] = a[0] == b[0] ? max(a[1], b[1]) : (a[0] > b[0] ? max(a[1], b[0]) : max(a[0], b[1]));
    c[0] = max(a[0], b[0]);
}
int lca(int ans[], int u, int v) {
    ans[0] = ans[1] = 0;
    if (d[u] < d[v]) swap(u, v);
    for (int i = __lg(n); i >= 0; i--)
        if (d[f[u][i]] >= d[v]) upd(ans, ans, g[u][i]), u = f[u][i];
    if (u == v) return u;
    for (int i = __lg(n); i >= 0; i--)
        if (f[u][i] != f[v][i]) {
            upd(ans, ans, g[u][i]), upd(ans, ans, g[v][i]);
            u = f[u][i], v = f[v][i];
        }
    upd(ans, ans, g[u][0]), upd(ans, ans, g[v][0]);
    return f[u][0];
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e + 1, e + m + 1, [](auto x, auto y) { return x.w < y.w; });
    iota(p + 1, p + n + 1, 1);
    long long mst = 0;
    for (int i = 1; i <= m; i++) {
        int x = find(e[i].u), y = find(e[i].v);
        if (x != y) {
            p[x] = y, v[i] = 1, mst += e[i].w;
            t[e[i].u].emplace_back(e[i].v, e[i].w);
            t[e[i].v].emplace_back(e[i].u, e[i].w);
        }
    }
    dfs(1, 0);
    for (int i = 1; i <= __lg(n); i++)
        for (int u = 1; u <= n; u++) {
            f[u][i] = f[f[u][i - 1]][i - 1];
            upd(g[u][i], g[u][i - 1], g[f[u][i - 1]][i - 1]);
        }
    int dlt = 1 << 30;
    for (int i = 1, mnv[2]; i <= m; i++) {
        if (v[i] || e[i].u == e[i].v) continue;
        lca(mnv, e[i].u, e[i].v);
        if (mnv[0] < e[i].w)
            dlt = min(dlt, e[i].w - mnv[0]);
        else if (mnv[1] != -1)
            dlt = min(dlt, e[i].w - mnv[1]);
    }
    cout << mst + dlt;
    return 0;
}