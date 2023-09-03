#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e4 + 5;
int n, m;
vector<pair<int, int>> g[N];

int res;
multiset<int> s[N];
int dfs(int u, int p, int k) {
    s[u].clear();
    for (const auto &[v, w] : g[u])
        if (v != p) {
            int val = dfs(v, u, k) + w;
            if (val >= k)
                res++;
            else
                s[u].insert(val);
        }
    int mxn = 0;
    while (!s[u].empty()) {
        if (s[u].size() == 1) return max(mxn, *s[u].begin());
        auto it = s[u].lower_bound(k - *s[u].begin());
        if (it == s[u].begin() && s[u].count(*it) == 1) ++it;
        if (it == s[u].end()) {
            mxn = max(mxn, *s[u].begin());
            s[u].erase(s[u].begin());
        } else {
            res++;
            s[u].erase(it), s[u].erase(s[u].begin());
        }
    }
    return mxn;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w), g[v].emplace_back(u, w);

    int l = 1, r = 1 << 30;
    while (l < r) {
        int k = (l + r + 1) >> 1;
        res = 0, dfs(1, 0, k);
        res >= m ? l = k : r = k - 1;
    }
    cout << l;
    return 0;
}