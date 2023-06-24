#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, K = N * 20;
int src[N];
long long val[K];
int idx, rt[N], ls[K], rs[K];

#define ls ls[p]
#define rs rs[p]
inline void pushup(int p)
{
    val[p] = val[ls] + val[rs];
}
void build(int &p, int l, int r)
{
    p = ++idx;
    if (l == r)
        return val[p] = src[l], void();
    int m = (l + r) >> 1;
    build(ls, l, m), build(rs, m + 1, r);
    pushup(p);
}
void modify(int &p, int l, int r, int x, int v)
{
    !p && (p = ++idx);
    val[p] += v;
    if (l == r)
        return;
    int m = (l + r) >> 1;
    if (x <= m)
        modify(ls, l, m, x, v);
    else
        modify(rs, m + 1, r, x, v);
}
#undef ls
#undef rs
int merge(int p, int q)
{
    if (!p || !q)
        return p | q;
    ls[p] = merge(ls[p], ls[q]), rs[p] = merge(rs[p], rs[q]);
    val[p] += val[q];
    return p;
}
void split(int p, int &q, int l, int r, int k)
{
    if (!p)
        return q = 0, void();
    q = ++idx;
    int m = (l + r) >> 1;
    if (k < m)
        swap(rs[p], rs[q]), split(ls[p], ls[q], l, m, k);
    else if (k == m)
        swap(rs[p], rs[q]);
    else
        split(rs[p], rs[q], m + 1, r, k);
    pushup(p), pushup(q);
}
long long query(int p, int l, int r, int ql, int qr)
{
    if ((ql <= l && r <= qr) || !p)
        return val[p];
    int m = (l + r) >> 1;
    long long ans = 0;
    if (ql <= m)
        ans += query(ls[p], l, m, ql, qr);
    if (qr > m)
        ans += query(rs[p], m + 1, r, ql, qr);
    return ans;
}
int kth(int p, int l, int r, long long k)
{
    if (l == r)
        return l;
    int m = (l + r) >> 1;
    if (k <= val[ls[p]])
        return kth(ls[p], l, m, k);
    else
        return kth(rs[p], m + 1, r, k - val[ls[p]]);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> src[i];
    build(rt[1], 1, n);
    for (int op, p, cur = 1; m--;)
    {
        cin >> op >> p;
        int x, y, z, t, q;
        switch (op)
        {
        case 0:
            cin >> x >> y;
            split(rt[p], rt[++cur], 1, n, x - 1), split(rt[cur], z, 1, n, y);
            rt[p] = merge(rt[p], z);
            break;
        case 1:
            cin >> t;
            rt[p] = merge(rt[p], rt[t]);
            break;
        case 2:
            cin >> x >> q;
            modify(rt[p], 1, n, q, x);
            break;
        case 3:
            cin >> x >> y;
            cout << query(rt[p], 1, n, x, y) << '\n';
            break;
        case 4:
            long long k;
            cin >> k;
            cout << (k <= val[rt[p]] ? kth(rt[p], 1, n, k) : -1) << '\n';
            break;
        }
    }
    return 0;
}