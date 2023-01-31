#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;
int tot, n, m;
int per_seg[(MAXN << 5) + 10],
    rt[MAXN + 10], ls[(MAXN << 5) + 10], rs[(MAXN << 5) + 10];
int src[MAXN + 10];
// int len, ind[MAXN + 10]; // 离散化数组

void build(int &rt, int l, int r)
{
    rt = ++tot;
    if (l == r)
    {
        per_seg[rt] = src[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls[rt], l, mid), build(rs[rt], mid + 1, r);
}
void modify(int &tr, int prev, int l, int r, int ins_p, int val)
{
    tr = ++tot;
    ls[tr] = ls[prev], rs[tr] = rs[prev];
    per_seg[tr] = per_seg[prev];
    if (l == r)
    {
        per_seg[tr] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (ins_p <= mid)
        modify(ls[tr], ls[prev], l, mid, ins_p, val);
    else
        modify(rs[tr], rs[prev], mid + 1, r, ins_p, val);
}
int query(int tr, int l, int r, int q)
{
    if (l == r)
        return per_seg[tr];
    int mid = (l + r) >> 1;
    if (q <= mid)
        return query(ls[tr], l, mid, q);
    else
        return query(rs[tr], mid + 1, r, q);
}

int main()
{
    ios::sync_with_stdio(false); // 史上最简单有效的快读
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> src[i];
    build(rt[0], 1, n);
    int ver, op, loc, val;
    for (int i = 1; i <= m; i++)
    {
        cin >> ver >> op;
        if (op == 1)
        {
            cin >> loc >> val;
            modify(rt[i], rt[ver], 1, n, loc, val);
        }
        else
        {
            cin >> loc;
            cout << query(rt[ver], 1, n, loc) << endl;
            rt[i] = rt[ver];
        }
    }
    return 0;
}