#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, b[N];
struct {
    int val, idx, prv, nxt;
    friend bool operator<(auto x, auto y) { return x.val < y.val; }
} a[N];
pair<int, int> ans[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].val, a[i].idx = i;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) b[a[i].idx] = i, a[i].prv = i - 1, a[i].nxt = i + 1;
    int l = 1, r = n;
    for (int i = n; i > 1; i--) {
        if (b[i] == r) {
            ans[i].first = a[r].val - a[a[r].prv].val;
            ans[i].second = a[a[r].prv].idx;
            r = a[r].prv;
        } else if (b[i] == l) {
            ans[i].first = a[a[l].nxt].val - a[l].val;
            ans[i].second = a[a[l].nxt].idx;
            l = a[l].nxt;
        } else {
            int suf = a[a[b[i]].nxt].val - a[b[i]].val,
                pre = a[b[i]].val - a[a[b[i]].prv].val;
            if (pre <= suf)
                ans[i] = {pre, a[a[b[i]].prv].idx};
            else
                ans[i] = {suf, a[a[b[i]].nxt].idx};
        }
        a[a[b[i]].prv].nxt = a[b[i]].nxt;
        a[a[b[i]].nxt].prv = a[b[i]].prv;
    }
    for (int i = 2; i <= n; i++) cout << ans[i].first << ' ' << ans[i].second << '\n';
    return 0;
}