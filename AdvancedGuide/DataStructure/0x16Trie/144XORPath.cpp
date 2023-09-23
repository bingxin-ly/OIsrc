#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, ans, idx, son[N << 5][2];
vector<pair<int, int> > g[N];

int d[N];
void precalc(int u, int p) {
    for (const auto &[v, w] : g[u])
        if (v != p) d[v] = d[u] ^ w, precalc(v, u);
}
void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int u = x >> i & 1;
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
}
int search(int x) {
    int p = 0, r = 0;
    for (int i = 30; i >= 0; i--) {
        int u = x >> i & 1;
        if (son[p][u ^ 1])
            p = son[p][u ^ 1], r |= 1 << i;
        else
            p = son[p][u];
    }
    return r;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, u++, v++,
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    precalc(1, 0);
    for (int i = 1; i <= n; i++)
        ans = max(ans, search(d[i])), insert(d[i]);
    cout << ans;
    return 0;
}