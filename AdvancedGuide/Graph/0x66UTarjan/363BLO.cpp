#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m;
vector<int> g[N];

int tim, dfn[N], low[N], siz[N], cut[N];
long long ans[N];
void tarjan(int u, int p) {
    dfn[u] = low[u] = ++tim, siz[u] = 1;
    int sum = 1;
    for (int v : g[u])
        if (!dfn[v]) {
            tarjan(v, u), siz[u] += siz[v], low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u] && (dfn[u] > 1 || g[u].size() > 1))
                cut[u] = 1, ans[u] += 1ll * siz[v] * (n - siz[v]), sum += siz[v];
        } else if (v != p)
            low[u] = min(low[u], dfn[v]);
    if (cut[u])
        ans[u] += n - 1 + 1ll * sum * (n - sum);
    else
        ans[u] = 2 * (n - 1);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    tarjan(1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
    return 0;
}