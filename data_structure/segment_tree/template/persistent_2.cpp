#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2 * 1e5;
int tot, n, m;
int per_seg[(MAXN << 5) + 10], src[MAXN + 10],
    rt[MAXN + 10], ls[(MAXN << 5) + 10], rs[(MAXN << 5) + 10];
int len, ind[MAXN + 10]; // 离散化数组

int build(int l, int r)
{
    int rt = ++tot;
    if (l == r)
        return rt;
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid), rs[rt] = build(mid + 1, r);
    return rt;
}
int modify(int p, int l, int r, int prev)
{
    int tr = ++tot;
    ls[tr] = ls[prev], rs[tr] = rs[prev];
    per_seg[tr] = per_seg[prev] + 1;
    if (l == r)
        return tr;
    int mid = (l + r) >> 1;
    if (p <= mid)
        ls[tr] = modify(p, l, mid, ls[prev]);
    else
        rs[tr] = modify(p, mid + 1, r, rs[prev]);
    return tr;
}
int query(int tr, int prev, int l, int r, int kth)
{
    int mid = (l + r) >> 1;
    int x = per_seg[ls[prev]] - per_seg[ls[tr]];
    if (l == r)
        return l;
    if (kth <= x)
        return query(ls[tr], ls[prev], l, mid, kth);
    else
        return query(rs[tr], rs[prev], mid + 1, r, kth - x);
}

int main()
{
    ios::sync_with_stdio(false); // 史上最简单有效的快读
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> src[i], ind[i] = src[i];
    sort(ind + 1, ind + 1 + n);
    len = unique(ind + 1, ind + 1 + n) - ind - 1;
    rt[0] = build(1, len);
    for (int i = 1; i <= n; i++)
    {
        int p = lower_bound(ind + 1, ind + 1 + len, src[i]) - ind;
        rt[i] = modify(p, 1, len, rt[i - 1]);
    }
    int l, r, k;
    for (int i = 1; i <= m; i++)
    {
        cin >> l >> r >> k;
        cout << ind[query(rt[l - 1], rt[r], 1, len, k)] << endl;
    }
    return 0;
}