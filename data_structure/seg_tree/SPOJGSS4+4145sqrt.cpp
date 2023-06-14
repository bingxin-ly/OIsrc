#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int tr[N << 2], src[N];

#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p)
{
    tr[p] = tr[ls] + tr[rs];
}
void build(int p, int l, int r)
{
    if (l == r)
        return tr[p] = src[l], void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p);
}
void update(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr && tr[p] == r - l + 1)
        return;
    if (l == r)
        return tr[p] = sqrt(tr[p]), void();

    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(ls, l, mid, ql, qr);
    if (qr > mid)
        update(rs, mid + 1, r, ql, qr);
    pushup(p);
}
int query(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return tr[p];

    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid)
        res += query(ls, l, mid, ql, qr);
    if (qr > mid)
        res += query(rs, mid + 1, r, ql, qr);
    return res;
}

signed main()
{
    int n, m, t = 0;
    while (~scanf("%lld", &n))
    {
        for (int i = 1; i <= n; i++)
            scanf("%lld", src + i);
        build(1, 1, n);

        scanf("%lld", &m);
        // printf("Case #%lld:\n", ++t);
        for (int opt, l, r; m--;)
        {
            scanf("%lld%lld%lld", &opt, &l, &r);
            if (l > r)
                l ^= r ^= l ^= r;
            if (opt)
                printf("%lld\n", query(1, 1, n, l, r));
            else
                update(1, 1, n, l, r);
        }
        // putchar('\n');
    }
    return 0;
}