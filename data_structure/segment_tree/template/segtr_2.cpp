// 区间乘线段树，completed!!
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
signed mod, src[N];
int tr[N << 2], addt[N << 2], mult[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p)
{
    tr[p] = (tr[ls] + tr[rs]) % mod;
}
void pushdown(int p, int l, int r)
{
    int mid = (l + r) >> 1;
    (((tr[ls] *= mult[p]) %= mod) += (mid - l + 1) * addt[p] % mod) %= mod;
    (((tr[rs] *= mult[p]) %= mod) += (r - mid) * addt[p] % mod) %= mod;

    (mult[ls] *= mult[p]) %= mod, (mult[rs] *= mult[p]) %= mod;

    (((addt[ls] *= mult[p]) %= mod) += addt[p]) %= mod;
    (((addt[rs] *= mult[p]) %= mod) += addt[p]) %= mod;
    mult[p] = 1, addt[p] = 0;
}

void build(int p, int l, int r)
{
    mult[p] = 1;
    if (l == r)
        return tr[p] = src[l], void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p);
}
void add(int p, int l, int r, int ql, int qr, int v)
{
    if (ql <= l && r <= qr)
    {
        (tr[p] += (r - l + 1) * v % mod) %= mod;
        (addt[p] += v) %= mod;
        return;
    }

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        add(ls, l, mid, ql, qr, v);
    if (qr > mid)
        add(rs, mid + 1, r, ql, qr, v);
    pushup(p);
}
void multiply(int p, int l, int r, int ql, int qr, int v)
{
    if (ql <= l && r <= qr)
    {
        (tr[p] *= v) %= mod;
        (addt[p] *= v) %= mod;
        (mult[p] *= v) %= mod;
        return;
    }

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        multiply(ls, l, mid, ql, qr, v);
    if (qr > mid)
        multiply(rs, mid + 1, r, ql, qr, v);
    pushup(p);
}
int query(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return tr[p];

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid)
        (res += query(ls, l, mid, ql, qr)) %= mod;
    if (qr > mid)
        (res += query(rs, mid + 1, r, ql, qr)) %= mod;
    pushup(p);
    return res;
}

signed main()
{
    int n, m;
    scanf("%lld%lld%d", &n, &m, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%d", src + i), src[i] %= mod;
    build(1, 1, n);

    for (int opt, x, y, k; m--;)
    {
        scanf("%lld%lld%lld", &opt, &x, &y);
        if (opt == 1)
            scanf("%lld", &k), multiply(1, 1, n, x, y, k);
        else if (opt == 2)
            scanf("%lld", &k), add(1, 1, n, x, y, k);
        else
            printf("%lld\n", query(1, 1, n, x, y));
    }
    return 0;
}