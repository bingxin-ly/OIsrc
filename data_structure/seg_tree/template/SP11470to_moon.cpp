#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
struct
{
    int ls, rs, tag;
    long long val;
} t[N << 5];
#define ls t[p].ls
#define rs t[p].rs
int idx, cur, rt[N];

void pushup(int p, int l, int r) { t[p].val = t[ls].val + t[rs].val + t[p].tag * (r - l + 1ll); }
void build(int &p, int l, int r)
{
    p = ++idx;
    if (l == r)
        return cin >> t[p].val, void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p, l, r);
}
void change(int &p, int l, int r, int ql, int qr, int v)
{
    t[++idx] = t[p], p = idx;
    if (ql <= l && r <= qr)
    {
        t[p].val += v * (r - l + 1);
        t[p].tag += v;
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid)
        change(ls, l, mid, ql, qr, v);
    if (qr > mid)
        change(rs, mid + 1, r, ql, qr, v);
    pushup(p, l, r);
}
long long query(int p, int l, int r, int ql, int qr, long long dlt)
{
    if (!p || (ql <= l && r <= qr))
        return t[p].val + dlt * (r - l + 1);
    int mid = (l + r) >> 1;
    long long ret = 0;
    dlt += t[p].tag;
    if (ql <= mid)
        ret += query(ls, l, mid, ql, qr, dlt);
    if (qr > mid)
        ret += query(rs, mid + 1, r, ql, qr, dlt);
    return ret;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    build(rt[0], 1, n);
    char op;
    for (int l, r, x; m--;)
    {
        cin >> op;
        if (op == 'C')
            cin >> l >> r >> x, rt[cur + 1] = rt[cur], change(rt[++cur], 1, n, l, r, x);
        else if (op == 'Q')
            cin >> l >> r, cout << query(rt[cur], 1, n, l, r, 0) << '\n';
        else if (op == 'H')
            cin >> l >> r >> x, cout << query(rt[x], 1, n, l, r, 0) << '\n';
        else
            cin >> x, cur = x;
    }
    return 0;
}