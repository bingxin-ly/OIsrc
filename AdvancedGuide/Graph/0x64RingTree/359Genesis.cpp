#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, a[N], idx = 1, hed[N], nxt[N << 1], ver[N << 1];
void link(int u, int v) {
    ver[++idx] = v, nxt[idx] = hed[u], hed[u] = idx;
}

int tim, dfn[N], frm[N], rot, brk, f[N][2], vis[N];
void dfs(int u) {
    dfn[u] = ++tim;
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = ver[i];
        if (!dfn[v])
            frm[v] = i, dfs(v);
        else if ((i ^ 1) != frm[u] && dfn[v] >= dfn[u])
            brk = i, rot = a[u] == v ? u : v;
    }
}
void dp(int u, int t) {
    f[u][0] = f[u][1] = 0, vis[u] = 1;
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = ver[i];
        if (!vis[v] && i != brk && (i ^ 1) != brk)
            dp(v, t), f[u][0] += max(f[v][0], f[v][1]);
    }
    if (t && u == a[rot])
        f[u][1] = f[u][0] + 1; // 因为 p -> a[p] 所以不需要不选额外的节点
    else
        for (int i = hed[u]; i; i = nxt[i]) {
            int v = ver[i];
            if (!vis[v] && i != brk && (i ^ 1) != brk)
                f[u][1] = max(f[u][1], f[u][0] - max(f[v][0], f[v][1]) + f[v][0] + 1);
        }
    vis[u] = 0;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], link(i, a[i]), link(a[i], i);
    int sum = 0;
    for (int u = 1, ans; u <= n; u++)
        if (!dfn[u]) {
            dfs(u);
            dp(rot, 0), ans = max(f[rot][0], f[rot][1]);
            dp(rot, 1), ans = max(ans, f[rot][0]);
            sum += ans;
        }
    cout << sum;
    return 0;
}