#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, m;
vector<int> g[N];
vector<pair<int, int> > q[N];

int p[N];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

int a[N], b[N], c[N], vis[N], dep[N], ans[N << 2];
void tarjan(int u) {
    vis[u] = 1;
    for (int v : g[u])
        if (!vis[v]) dep[v] = dep[u] + 1, tarjan(v), p[v] = u;
    for (const auto &[v, i] : q[u])
        if (vis[v] == 2 || v == u) ans[i] = find(v);
    vis[u] = 2;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    for (int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i] >> c[i];
        q[a[i]].emplace_back(b[i], i), q[b[i]].emplace_back(a[i], i);
        q[b[i]].emplace_back(c[i], i + m), q[c[i]].emplace_back(b[i], i + m);
        q[a[i]].emplace_back(c[i], i + 2 * m), q[c[i]].emplace_back(a[i], i + 2 * m);
    }
    iota(p + 1, p + n + 1, 1), tarjan(1);
    for (int i = 1; i <= m; i++) {
        int ab = ans[i], bc = ans[i + m], ac = ans[i + 2 * m];
        int pos, ans;
        if (dep[ab] >= dep[bc] && dep[ab] >= dep[ac])
            pos = ab, ans = dep[a[i]] - dep[ac] + dep[b[i]] - dep[ab] + dep[c[i]] - dep[ac];
        else if (dep[bc] >= dep[ab] && dep[bc] >= dep[ac])
            pos = bc, ans = dep[b[i]] - dep[ab] + dep[c[i]] - dep[bc] + dep[a[i]] - dep[ab];
        else
            pos = ac, ans = dep[a[i]] - dep[ab] + dep[c[i]] - dep[ac] + dep[b[i]] - dep[ab];
        cout << pos << ' ' << ans << '\n';
    }
    return 0;
}