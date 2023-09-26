#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 1e5 + 9;
int n, m;

struct {
    int val, tag;
} t[N << 2];
#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p) { t[p].val = t[ls].val + t[rs].val; }
void pushtag(int p, int l, int r, int v) {
    t[p].val += (r - l + 1) * v;
    t[p].tag += v;
}
void pushdown(int p, int l, int r) {
    if (t[p].tag) {
        int m = (l + r) >> 1;
        pushtag(ls, l, m, t[p].tag), pushtag(rs, m + 1, r, t[p].tag);
        t[p].tag = 0;
    }
}
void build(int p, int l, int r) {
    if (l == r) return cin >> t[p].val, void();
    int m = (l + r) >> 1;
    build(ls, l, m), build(rs, m + 1, r);
    pushup(p);
}
void update(int p, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) return pushtag(p, l, r, v);
    pushdown(p, l, r);
    int m = (l + r) >> 1;
    if (ql <= m) update(ls, l, m, ql, qr, v);
    if (qr > m) update(rs, m + 1, r, ql, qr, v);
    pushup(p);
}
int query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return t[p].val;
    pushdown(p, l, r);
    int m = (l + r) >> 1, ret = 0;
    if (ql <= m) ret += query(ls, l, m, ql, qr);
    if (qr > m) ret += query(rs, m + 1, r, ql, qr);
    return ret;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m, build(1, 1, n);
    for (int o, x, y, k; m--;) {
        cin >> o >> x >> y;
        if (o == 1)
            cin >> k, update(1, 1, n, x, y, k);
        else
            cout << query(1, 1, n, x, y) << '\n';
    }
    return 0;
}