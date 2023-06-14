#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
struct tree
{
    int l, r;
    int sum, lmx, rmx, mxn;
    tree() { sum = 0, lmx = rmx = mxn = ~0x3f3f3f3f; }
} t[N << 2];
int arr[N];

inline int max(int a, int b) { return a > b ? a : b; }
void pushup(tree &p, tree &ls, tree &rs)
{
    p.sum = ls.sum + rs.sum;

    p.lmx = max(ls.lmx, ls.sum + rs.lmx);
    p.rmx = max(ls.rmx + rs.sum, rs.rmx);
    p.mxn = max(max(ls.mxn, rs.mxn), ls.rmx + rs.lmx);
}

#define ls p << 1
#define rs p << 1 | 1
void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if (l == r)
        return t[p].sum = t[p].lmx = t[p].rmx = t[p].mxn = arr[l], void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(t[p], t[ls], t[rs]);
}
void modify(int p, int pos, int x)
{
    if (t[p].l == t[p].r)
        return t[p].sum = t[p].lmx = t[p].rmx = t[p].mxn = x, void();

    int mid = (t[p].l + t[p].r) >> 1;
    if (pos <= mid)
        modify(ls, pos, x);
    else
        modify(rs, pos, x);
    pushup(t[p], t[ls], t[rs]);
}
tree query(int p, int ql, int qr)
{
    if (ql <= t[p].l && t[p].r <= qr)
        return t[p];

    int mid = (t[p].l + t[p].r) >> 1;
    tree ret, lt, rt;
    if (ql <= mid)
        lt = query(ls, ql, qr);
    if (qr > mid)
        rt = query(rs, ql, qr);
    pushup(ret, lt, rt);
    return ret;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    build(1, 1, n);

    for (int op, x, y; q--;)
    {
        cin >> op >> x >> y;
        if (op == 2)
            modify(1, x, y);
        else
        {
            if (x > y)
                swap(x, y);
            cout << query(1, x, y).mxn << '\n';
        }
    }
    return 0;
}