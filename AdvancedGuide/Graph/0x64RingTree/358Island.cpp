#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, idx = 1, hed[N], nxt[N << 1], ver[N << 1], len[N << 1];
void link(int u, int v, int w) {
    ver[++idx] = v, len[idx] = w, nxt[idx] = hed[u], hed[u] = idx;
}

int tim, dfn[N], vis[N], frm[N];
int p, r[N << 1];
long long s[N << 1];
void cycle(int u, int v, int w) {
    s[1] = w;
    while (v != u)
        r[++p] = v, s[p + 1] = len[frm[v]], v = ver[frm[v] ^ 1];
    r[++p] = v;
    for (int i = 1; i <= p; i++)
        vis[r[i]] = 1, r[i + p] = r[i], s[i + p] = s[i];
    for (int i = 1; i <= p << 1; i++)
        s[i] += s[i - 1];
}
void dfs(int u) {
    dfn[u] = ++tim;
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = ver[i];
        if (!dfn[v])
            frm[v] = i, dfs(v);
        else if ((i ^ 1) != frm[u] && dfn[v] < dfn[u])
            cycle(v, u, len[i]);
    }
}
long long d[N], ans, sum;
void dp(int u) {
    vis[u] = 1;
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = ver[i], w = len[i];
        if (!vis[v]) {
            dp(v);
            ans = max(ans, d[v] + d[u] + w);
            d[u] = max(d[u], d[v] + w);
        }
    }
}
int h, t, q[N << 1];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int u = 1, v, w; u <= n; u++)
        cin >> v >> w, link(u, v, w), link(v, u, w);
    for (int u = 1; u <= n; u++)
        if (!dfn[u]) {
            p = ans = 0, dfs(u);
            for (int i = 1; i <= p; i++) dp(r[i]);
            h = t = 1, q[1] = 1;
            for (int i = 2; i <= p << 1; i++) {
                while (h <= t && q[h] <= i - p) h++;
                ans = max(ans, d[r[q[h]]] + d[r[i]] + s[i] - s[q[h]]);
                while (h <= t && d[r[q[t]]] - s[q[t]] <= d[r[i]] - s[i]) t--;
                q[++t] = i;
            }
            sum += ans;
        }
    cout << sum;
    return 0;
}