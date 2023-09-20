#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, m, u[N], v[N], w[N];
vector<pair<int, int> > t[N];

int fa[N], dep[N], pte[N];
void dfs(int u, int p) {
    fa[u] = p, dep[u] = dep[p] + 1;
    for (pair<int, int> pr : t[u]) {
        int v = pr.first, i = pr.second;
        if (v != p) pte[v] = i, dfs(v, u);
    }
}
int p[N], cnt, col[N];
int f(int x) { return x == p[x] ? x : p[x] = f(p[x]); }
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        if (w[i]) t[u[i]].emplace_back(v[i], i), t[v[i]].emplace_back(u[i], i);
    }
    iota(p + 1, p + n + 1, 1), dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        vector<int> cyc;
        int x = u[i], y = v[i];
        while (f(x) != f(y)) { // 这里直接用并查集的父亲来代替树剖的 top
            if (dep[f(x)] < dep[f(y)]) swap(x, y);
            x = f(x), p[x] = f(fa[x]);
            cyc.emplace_back(pte[x]);
        }
        sort(cyc.begin(), cyc.end());
        for (int j : cyc) col[j] = ++cnt;
        if (!w[i]) col[i] = ++cnt;
    }
    for (int i = 1; i <= m; i++) cout << col[i] << ' ';
    return 0;
}