#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e6 + 9;
int n, m, k, q;
long long ans[N];
struct Query {
    int op, l, r, c, t;
} qu[N];
struct Solver {
    int sum, col[N], nxt[N];
    void modify(int ql, int qr) {
        int lst = 0;
        for (int i = ql; i <= qr; i = nxt[i]) {
            sum += !col[i], col[i] = 1;
            if (lst) nxt[lst] = nxt[qr];
            lst = i;
        }
    }
    int query(int ql, int qr) {
        int cnt = 0;
        for (int i = ql; i <= qr; i = nxt[i]) cnt += !col[i];
        return qr - ql + 1 - cnt;
    }
} row, col;

void update(int i) {
    int l = qu[i].l, r = qu[i].r, c = qu[i].c;
    if (qu[i].op == 1) {
        int cntr = row.query(l, r), cntc = col.sum;
        ans[c] += 1ll * (r - l + 1 - cntr) * (m - cntc);
        row.modify(l, r);
    } else {
        int cntr = row.sum, cntc = col.query(l, r);
        ans[c] += 1ll * (n - cntr) * (r - l + 1 - cntc);
        col.modify(l, r);
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k >> q;
    for (int i = 1; i <= q; i++)
        cin >> qu[i].op >> qu[i].l >> qu[i].r >> qu[i].c >> qu[i].t;
    iota(row.nxt + 1, row.nxt + n + 1, 2), iota(col.nxt + 1, col.nxt + m + 1, 2);
    for (int i = q; i >= 1; i--)
        if (qu[i].t) update(i);
    for (int i = 1; i <= q; i++)
        if (!qu[i].t) update(i);
    for (int i = 1; i <= k; i++) cout << ans[i] << ' ';
    return 0;
}