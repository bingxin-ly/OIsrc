#define mid ((l + r) >> 1)
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int n, m, cnt, src[MAXN], lazy[MAXN << 1];
struct node
{
    int l, r;
    int add, sum;
} seg_tr[MAXN << 1];

inline void push_up(int nd) // 也可以理解成push_to_here
{
    node pa = seg_tr[nd], ls = seg_tr[pa.l], rs = seg_tr[pa.r];
    pa.sum = ls.sum + rs.sum;
}
void push_down(int l, size_t r, int nd)
{
    node pa = seg_tr[nd];
    lazy[pa.l] += lazy[nd], lazy[pa.r] += lazy[nd];
    seg_tr[pa.l].sum += (mid - l + 1) * lazy[nd],
        seg_tr[pa.r].sum += (r - mid) * lazy[nd];
    lazy[nd] = 0;
}
void build(int &p, int l, int r)
{
    if (!p)
        p = ++cnt;
    if (l == r)
    {
        seg_tr[p].sum = src[l];
        return;
    }
    build(seg_tr[p].l, l, mid), build(seg_tr[p].r, mid + 1, r);
    push_up(p);
}
void modify(int &p, int l, int r, int ql, int qr, int val)
