#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10, INF = 2e9;
struct segment_tree
{
    int l, r;
    long long sum;
    int mxa, mxb, cnt, sem;
    int add1, add2, add3, add4;
} t[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p)
{
    t[p].sum = t[ls].sum + t[rs].sum;
    t[p].mxa = max(t[ls].mxa, t[rs].mxa);
    t[p].mxb = max(t[ls].mxb, t[rs].mxb);
    if (t[ls].mxa == t[rs].mxa)
        t[p].sem = max(t[ls].sem, t[rs].sem),
        t[p].cnt = t[ls].cnt + t[rs].cnt;
    /* else if (t[ls].mxa > t[rs].mxa)
        t[p].sem = max(t[ls].sem, t[rs].mxa),
        t[p].cnt = t[ls].cnt;
    else
        t[p].sem = max(t[ls].mxa, t[rs].sem),
        t[p].cnt = t[rs].cnt; */
    else
        t[p].sem = max(t[ls].sem, t[rs].sem),
        t[p].sem = max(t[p].sem, min(t[ls].mxa, t[rs].mxb)),
        t[p].cnt = t[ls].mxa > t[rs].mxa ? t[ls].cnt : t[rs].cnt;
}
void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if (l == r)
    {
        cin >> t[p].sum;
        t[p].mxa = t[p].mxb = t[p].sum;
        t[p].cnt = 1, t[p].sem = -INF;
        return;
    }

    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p);
}

void spread(int p, long long t1, long long t2, int t3, int t4)
{
    t[p].sum += t1 * t[p].cnt + t2 * (t[p].r - t[p].l + 1 - t[p].cnt);
    t[p].mxb = max(t[p].mxb, t[p].mxa + t3), t[p].mxa += t1;

    if (t[p].sem != -INF)
        t[p].sem += t2;

    t[p].add3 = max(t[p].add3, t[p].add1 + t3);
    t[p].add4 = max(t[p].add4, t[p].add2 + t4);
    t[p].add1 += t1, t[p].add2 += t2;
}
void pushdown(int p)
{
    int maxn = max(t[ls].mxa, t[rs].mxa);
    if (t[ls].mxa == maxn)
        spread(ls, t[p].add1, t[p].add2, t[p].add3, t[p].add4);
    else
        spread(ls, t[p].add2, t[p].add2, t[p].add4, t[p].add4);

    if (t[rs].mxa == maxn)
        spread(rs, t[p].add1, t[p].add2, t[p].add3, t[p].add4);
    else
        spread(rs, t[p].add2, t[p].add2, t[p].add4, t[p].add4);
    t[p].add1 = t[p].add2 = t[p].add3 = t[p].add4 = 0;
}

int ql, qr;
long long v;
void uadd(int p)
{
    if (ql > t[p].r || qr < t[p].l)
        return;
    if (ql <= t[p].l && t[p].r <= qr)
    {
        t[p].sum += v * t[p].cnt + v * (t[p].r - t[p].l + 1 - t[p].cnt);
        t[p].mxa += v, t[p].mxb = max(t[p].mxb, t[p].mxa);
        if (t[p].sem != -INF)
            t[p].sem += v;
        t[p].add1 += v, t[p].add2 += v;
        t[p].add3 = max(t[p].add3, t[p].add1),
        t[p].add4 = max(t[p].add4, t[p].add2);
        return;
    }

    pushdown(p);
    uadd(ls), uadd(rs);
    pushup(p);
}
void umin(int p)
{
    if (ql > t[p].r || qr < t[p].l || v >= t[p].mxa)
        return;
    if (ql <= t[p].l && t[p].r <= qr && t[p].sem < v)
    {
        long long k = t[p].mxa - v;
        t[p].sum -= k * t[p].cnt;
        t[p].mxa = v, t[p].add1 -= k;
        return;
    }

    pushdown(p);
    umin(ls), umin(rs);
    pushup(p);
}

long long qsum(int p)
{
    if (ql > t[p].r || qr < t[p].l)
        return 0;
    if (ql <= t[p].l && t[p].r <= qr)
        return t[p].sum;

    pushdown(p);
    return qsum(ls) + qsum(rs);
}
int qmaxa(int p)
{
    if (ql > t[p].r || qr < t[p].l)
        return -INF;
    if (ql <= t[p].l && t[p].r <= qr)
        return t[p].mxa;

    pushdown(p);
    return max(qmaxa(ls), qmaxa(rs));
}
int qmaxb(int p)
{
    if (ql > t[p].r || qr < t[p].l)
        return -INF;
    if (ql <= t[p].l && t[p].r <= qr)
        return t[p].mxb;

    pushdown(p);
    return max(qmaxb(ls), qmaxb(rs));
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    build(1, 1, n);
    while (m--)
    {
        int op;
        cin >> op >> ql >> qr;
        switch (op)
        {
        case 1:
            cin >> v, uadd(1);
            break;
        case 2:
            cin >> v, umin(1);
            break;
        case 3:
            cout << qsum(1) << '\n';
            break;
        case 4:
            cout << qmaxa(1) << '\n';
            break;
        case 5:
            cout << qmaxb(1) << '\n';
            break;
        }
    }
    return 0;
}