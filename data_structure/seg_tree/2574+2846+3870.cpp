#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

const int N = 2e5 + 10;
int tr[N << 2];
bool src[N], tag[N << 2];

#define ls p << 1
#define rs p << 1 | 1
void pushup(int p)
{
    tr[p] = tr[ls] + tr[rs];
}
void pushdown(int p, int l, int r)
{
    if (tag[p])
    {
        int mid = (l + r) >> 1;
        tr[ls] = mid - l + 1 - tr[ls], tr[rs] = r - mid - tr[rs];

        tag[ls] ^= 1, tag[rs] ^= 1;
        tag[p] = false;
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
    return res;
}
void modify(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return tr[p] = r - l + 1 - tr[p], tag[p] ^= 1, void();

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        modify(ls, l, mid, ql, qr);
    if (qr > mid)
        modify(rs, mid + 1, r, ql, qr);
    pushup(p);
}

signed main()
{
    int n = read(), m = read();
    /* char c = getchar();
    for (int i = 1; i <= n; i++)
    {
        while (c != '1' && c != '0')
            c = getchar();
        src[i] = c - '0', c = getchar();
    } */
    build(1, 1, n);

    for (int op, l, r; m--;)
    {
        op = read(), l = read(), r = read();
        if (op)
            printf("%d\n", query(1, 1, n, l, r));
        else
            modify(1, 1, n, l, r);
    }
    return 0;
}