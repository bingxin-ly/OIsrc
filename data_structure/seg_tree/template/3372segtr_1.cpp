#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int tr[N << 2], tag[N << 2], src[N];

#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p)
{
    tr[p] = tr[ls] + tr[rs];
}
void pushdown(int p, int l, int r)
{
    if (tag[p])
    {
        int mid = (l + r) >> 1;
        tr[ls] += (mid - l + 1) * tag[p], tr[rs] += (r - mid) * tag[p];

        tag[ls] += tag[p], tag[rs] += tag[p];
        tag[p] = 0;
    }
}

void build(int p, int l, int r)
{
    if (l == r)
        return tr[p] = src[l], void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p);
}
void update(int p, int l, int r, int pos, int v)
{
    if (l == r)
        return tr[p] += v, void();

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(ls, l, mid, pos, v);
    else
        update(rs, mid + 1, r, pos, v);
    pushup(p);
}
void update(int p, int l, int r, int ql, int qr, int v)
{
    if (ql <= l && r <= qr)
        return tr[p] += (r - l + 1) * v, tag[p] += v, void();

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(ls, l, mid, ql, qr, v);
    if (qr > mid)
        update(rs, mid + 1, r, ql, qr, v);
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
        res += query(ls, l, mid, ql, qr);
    if (qr > mid)
        res += query(rs, mid + 1, r, ql, qr);
    pushup(p);
    return res;
}

signed main()
{
    int n, m;
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", src + i);
    build(1, 1, n);

    for (int opt, x, y, k; m--;)
    {
        scanf("%lld%lld%lld", &opt, &x, &y);
        if (opt == 1)
            scanf("%lld", &k), update(1, 1, n, x, y, k);
        else
            printf("%lld\n", query(1, 1, n, x, y));
    }
    return 0;
}