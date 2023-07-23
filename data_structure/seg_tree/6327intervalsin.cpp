#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int n, m;

// sin(α+β)=sinαcosβ+cosαsinβ
// cos(α+β)=cosαcosβ−sinαsinβ
// 先挂在这，我忘光了
double sina, cosa, sinb, cosb;
void assign(double sa, double ca, double sb, double cb) { sina = sa, cosa = ca, sinb = sb, cosb = cb; }
double sinplus() { return sina * cosb + cosa * sinb; }
double cosplus() { return cosa * cosb - sina * sinb; }

struct
{
    double sin, cos;
    long long tag;
} t[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
inline void pushup(int p)
{
    t[p].sin = t[ls].sin + t[rs].sin;
    t[p].cos = t[ls].cos + t[rs].cos;
}
inline void pushdown(int p)
{
    if (t[p].tag)
    {
        assign(t[ls].sin, t[ls].cos, sin(t[p].tag), cos(t[p].tag));
        t[ls].sin = sinplus(), t[ls].cos = cosplus();

        assign(t[rs].sin, t[rs].cos, sin(t[p].tag), cos(t[p].tag));
        t[rs].sin = sinplus(), t[rs].cos = cosplus();

        t[ls].tag += t[p].tag, t[rs].tag += t[p].tag, t[p].tag = 0;
    }
}
void build(int p, int l, int r)
{
    if (l == r)
        return cin >> l, t[p].sin = sin(l), t[p].cos = cos(l), void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p);
}
void update(int p, int l, int r, int ql, int qr, int v)
{
    if (ql <= l && r <= qr)
    {
        assign(t[p].sin, t[p].cos, sin(v), cos(v));
        t[p].sin = sinplus(), t[p].cos = cosplus(), t[p].tag += v;
        return;
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(ls, l, mid, ql, qr, v);
    if (qr > mid)
        update(rs, mid + 1, r, ql, qr, v);
    pushup(p);
}
double query(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return t[p].sin;
    pushdown(p);
    int mid = (l + r) >> 1;
    double ret = 0;
    if (ql <= mid)
        ret += query(ls, l, mid, ql, qr);
    if (qr > mid)
        ret += query(rs, mid + 1, r, ql, qr);
    return ret;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    build(1, 1, n);
    cin >> m;
    for (int op, l, r, x; m--;)
    {
        cin >> op >> l >> r;
        if (op == 1)
            cin >> x, update(1, 1, n, l, r, x);
        else
            cout << fixed << setprecision(1) << query(1, 1, n, l, r) << '\n';
    }
    return 0;
}