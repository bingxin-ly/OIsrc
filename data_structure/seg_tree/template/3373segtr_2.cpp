#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, MOD;
struct {
    int val, mul, add;
} t[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p) { t[p].val = (t[ls].val + t[rs].val) % MOD; }
void pushtag(int p, int l, int r, int add, int mul) {
    t[p].val = (t[p].val * mul % MOD + (r - l + 1) * add % MOD) % MOD;
    t[p].mul = t[p].mul * mul % MOD, t[p].add = (t[p].add * mul % MOD + add) % MOD;
}
void pushdown(int p, int l, int r) {
    int m = (l + r) >> 1;
    pushtag(ls, l, m, t[p].add, t[p].mul);
    pushtag(rs, m + 1, r, t[p].add, t[p].mul);
    t[p].mul = 1, t[p].add = 0;
}

void build(int p, int l, int r) {
    t[p].mul = 1, t[p].add = 0;
    if (l == r) return cin >> t[p].val, void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p);
}
void add(int p, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        (t[p].val += (r - l + 1) * v % MOD) %= MOD;
        (t[p].add += v) %= MOD;
        return;
    }

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) add(ls, l, mid, ql, qr, v);
    if (qr > mid) add(rs, mid + 1, r, ql, qr, v);
    pushup(p);
}
void multiply(int p, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        (t[p].val *= v) %= MOD;
        (t[p].add *= v) %= MOD, (t[p].mul *= v) %= MOD;
        return;
    }

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) multiply(ls, l, mid, ql, qr, v);
    if (qr > mid) multiply(rs, mid + 1, r, ql, qr, v);
    pushup(p);
}
int query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return t[p].val;

    pushdown(p, l, r);
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid) (res += query(ls, l, mid, ql, qr)) %= MOD;
    if (qr > mid) (res += query(rs, mid + 1, r, ql, qr)) %= MOD;
    return res;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> MOD, build(1, 1, n);
    for (int o, x, y, k; m--;) {
        cin >> o >> x >> y;
        if (o == 1)
            cin >> k, multiply(1, 1, n, x, y, k);
        else if (o == 2)
            cin >> k, add(1, 1, n, x, y, k);
        else
            cout << query(1, 1, n, x, y) << '\n';
    }
    return 0;
}