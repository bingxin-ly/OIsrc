#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e3 + 5;
int n, m;
vector<int> g[N];

int fr[N], st;
void ring(int u, int p) {
    if (fr[u]) return fr[st = u] = p, void();
    fr[u] = p;
    for (int v : g[u])
        if (v != p && !st) ring(v, u);
}
pair<int, int> del;
vector<int> res, cur;
void solve(int u, int p) {
    cur.emplace_back(u);
    sort(g[u].begin(), g[u].end());
    for (int v : g[u])
        if (v != p && del != make_pair(u, v) && del != make_pair(v, u))
            solve(v, u);
}
void comp() {
    if (res.empty()) return res = cur, void();
    for (int i = 0; i < n; i++)
        if (res[i] != cur[i]) {
            if (cur[i] < res[i]) res = cur;
            return;
        }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    if (m < n)
        solve(1, 0), comp();
    else {
        ring(1, 0);
        int p = st;
        do {
            del = {fr[p], p}, cur.clear();
            solve(1, 0), comp(), p = fr[p];
        } while (p != st);
    }
    for (int i : res) cout << i << ' ';
    return 0;
}