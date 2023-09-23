#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5;
int n, b[N], ans[N];
struct L {
    int val, idx, prv, nxt;
    friend bool operator<(L x, L y) { return x.val < y.val; }
} a[N];

void solve() {
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) b[a[i].idx] = i, a[i].prv = i - 1, a[i].nxt = i + 1;

    int pos = (n + 1) >> 1;
    ans[n + 2] = a[pos].val;
    for (int i = n; i > 1; i -= 2) {
        int p1 = b[i], p2 = b[i - 1];
        if (p1 > p2) swap(p1, p2);
        if (p1 >= pos)
            pos = a[pos].prv;
        else if (p2 <= pos)
            pos = a[pos].nxt;
        ans[i] = a[pos].val;

        a[a[p1].prv].nxt = a[p1].nxt, a[a[p1].nxt].prv = a[p1].prv;
        a[a[p2].prv].nxt = a[p2].nxt, a[a[p2].nxt].prv = a[p2].prv;
    }
    for (int i = 3; i <= n + 2; i += 2) {
        cout << ans[i] << ' ';
        if (!((i - 1) % 20)) cout << '\n';
    }
    if ((n + 1) % 20) cout << '\n';
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int p, _;
    cin >> p;
    while (p--) {
        cin >> _ >> n, cout << _ << ' ' << (n + 1) / 2 << '\n';
        for (int i = 1; i <= n; i++) cin >> a[i].val, a[i].idx = i;
        solve();
    }
    return 0;
}