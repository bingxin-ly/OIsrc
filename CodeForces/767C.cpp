#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, r, w[N], sum;
vector<int> g[N], ans;
void dfs(int u) {
    for (int v : g[u]) dfs(v), w[u] += w[v];
    if (w[u] == sum) ans.emplace_back(u), w[u] = 0;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int u = 1, p; u <= n; u++) {
        cin >> p >> w[u], sum += w[u];
        if (p)
            g[p].emplace_back(u);
        else
            r = u;
    }
    if (sum % 3) return cout << -1, 0;
    sum /= 3, dfs(r);
    if (ans.size() <= 2)
        cout << -1;
    else
        cout << ans[0] << ' ' << ans[1];
    return 0;
}