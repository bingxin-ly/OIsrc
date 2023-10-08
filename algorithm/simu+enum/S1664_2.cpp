#include <bits/stdc++.h>
using namespace std;

constexpr int M = 1e5 + 9;
int n, m, sum[M];
void insert(int p, int v) {
    for (; p <= m; p += p & -p) sum[p] += v;
}
int presum(int p) {
    int r = 0;
    for (; p; p -= p & -p) r += sum[p];
    return r;
}
struct seg {
    int l, r;
    seg(int l, int r) : l(l), r(r) {}
    friend bool operator<(const seg &x, const seg &y) {
        return x.r - x.l != y.r - y.l ? x.r - x.l < y.r - y.l : x.l < y.l;
    }
};
multiset<seg> s;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, l, r; i <= n; i++) cin >> l >> r, s.emplace(l, r);
    int cnt = n;
    for (int d = 1; d <= m; d++) {
        while (!s.empty() && s.begin()->r - s.begin()->l + 1 <= d) {
            auto it = s.begin();
            insert(it->l, 1), insert(it->r + 1, -1);
            s.erase(it), cnt--;
        }
        int ans = 0;
        for (int i = d; i <= m; i += d) ans += presum(i);
        cout << ans + cnt << '\n';
    }
    return 0;
}