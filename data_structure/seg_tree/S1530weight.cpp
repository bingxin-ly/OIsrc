#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9, M = 1e5 + 9;
int n, m, q, s, a[N];
vector<int> v;
struct ask {
    int op, l, r, x;
} p[N];

bool in[11];
bitset<M> cas[1030];
void update(int id) {
    cas[id][0] = 1;
    for (int i = 0; i < s; i++)
        if (in[i])
            for (int j = v[i]; j <= m; j++)
                cas[id][j] = cas[id][j] | cas[id][j - v[i]];
}

#define ls (p << 1)
#define rs (p << 1 | 1)
int val[N << 2], tag[N << 2];
void pushdown(int p) {
    if (tag[p]) val[ls] = val[rs] = val[p], tag[p] = 0, tag[ls] = tag[rs] = 1;
}
void build(int p, int l, int r) {
    if (l == r) return val[p] = 1 << (a[l] - 1), void();
    int m = (l + r) >> 1;
    build(ls, l, m), build(rs, m + 1, r);
    val[p] = val[ls] | val[rs];
}
void cover(int p, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) return val[p] = 1 << (v - 1), tag[p] = 1, void();
    pushdown(p);
    int m = (l + r) >> 1;
    if (ql <= m) cover(ls, l, m, ql, qr, v);
    if (qr > m) cover(rs, m + 1, r, ql, qr, v);
    val[p] = val[ls] | val[rs];
}
int query(int p, int l, int r, int ql, int qr) {
    if ((ql <= l && r <= qr) || tag[p]) return val[p];
    pushdown(p);
    int m = (l + r) >> 1, ret = 0;
    if (ql <= m) ret |= query(ls, l, m, ql, qr);
    if (qr > m) ret |= query(rs, m + 1, r, ql, qr);
    return ret;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], v.emplace_back(a[i]);
    for (int i = 1; i <= q; i++) {
        cin >> p[i].op >> p[i].l >> p[i].r >> p[i].x;
        if (p[i].op == 1) v.emplace_back(p[i].x);
    }
    sort(v.begin(), v.end()), v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    build(1, 1, n);

    s = v.size();
    for (int i = 0; i < 1 << s; i++) {
        for (int j = 0; j < s; j++) in[j] = i >> j & 1;
        update(i);
    }

    for (int i = 1; i <= q; i++)
        if (p[i].op == 1)
            cover(1, 1, n, p[i].l, p[i].r, lower_bound(v.begin(), v.end(), p[i].x) - v.begin() + 1);
        else {
            int pos = query(1, 1, n, p[i].l, p[i].r);
            cout << (cas[pos][p[i].x] ? "Yes\n" : "No\n");
        }
    return 0;
}
