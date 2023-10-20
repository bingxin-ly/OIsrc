#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e4 + 9;
int n, m, a[N], f[N][16];
vector<pair<int, int> > g[N];
long long dep[N];
void pre(int u, int p) {
    f[u][0] = p;
    for (const auto &[v, w] : g[u])
        if (v != p) dep[v] = dep[u] + w, pre(v, u);
}
pair<int, long long> climb(int u, long long lim) {
    for (int i = __lg(n); i >= 0; i--)
        if (f[u][i] > 1 && dep[u] - dep[f[u][i]] <= lim)
            lim -= dep[u] - dep[f[u][i]], u = f[u][i];
    return {u, lim};
}

int vis[N], cov[N], use[N];
vector<int> son;
void dfs(int u) {
    bool ok = true;
    for (const auto &[v, w] : g[u])
        if (dep[v] > dep[u]) {
            dfs(v), ok &= cov[v];
            if (u == 1 && !cov[v]) son.emplace_back(v);
        }
    cov[u] = vis[u] || (g[u].size() > 1 && ok);
}
bool solve(long long lim) {
    memset(vis, 0, sizeof(vis)), memset(cov, 0, sizeof(cov)), memset(use, 0, sizeof(use));
    vector<pair<long long, int> > sec;
    for (int i = 1; i <= m; i++) {
        auto [pos, res] = climb(a[i], lim);
        if (res <= dep[pos])
            vis[pos] = 1;
        else
            sec.emplace_back(res - dep[pos], pos);
    }
    son.clear(), dfs(1);
    sort(son.begin(), son.end(), [](int x, int y) { return dep[x] < dep[y]; });
    sort(sec.begin(), sec.end());
    for (int i = 0; i < (int)sec.size(); i++) {
        const auto &[res, pos] = sec[i];
        if (!cov[pos] && res < dep[pos]) cov[pos] = use[i] = 1;
    }
    for (int i = 0, j = 0; i < (int)son.size(); i++) {
        if (cov[son[i]]) continue;
        while (j < (int)sec.size() && (use[j] || sec[j].first < dep[son[i]])) j++;
        if (j == (int)sec.size()) return false;
        j++;
    }
    return true;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    long long rr = 1;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, rr += w,
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    pre(1, 0);
    for (int i = 1; i <= __lg(n); i++)
        for (int u = 1; u <= n; u++) f[u][i] = f[f[u][i - 1]][i - 1];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> a[i];
    long long l = 0, r = rr;
    while (l < r) {
        long long s = (l + r) >> 1;
        solve(s) ? r = s : l = s + 1;
    }
    cout << (l != rr ? l : -1);
    return 0;
}