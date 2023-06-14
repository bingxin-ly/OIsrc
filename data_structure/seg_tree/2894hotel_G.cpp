#include <bits/stdc++.h>
using namespace std;

// 和最大子段和还不太一样，自己真正做了才体会到
const int N = 5e5 + 10;
struct node
{
    int lm, rm, mx, len;
    int lazy;
} segtr[N << 2];

#define ls p << 1
#define rs p << 1 | 1
inline int max(int a, int b) { return a > b ? a : b; }
inline int max(int a, int b, int c) { return max(max(a, b), c); }
void build(int p, int l, int r)
{
    segtr[p].lm = segtr[p].rm = segtr[p].mx = segtr[p].len = r - l + 1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
}
void pushup(int p)
{
    if (segtr[ls].mx == segtr[ls].len)
        segtr[p].lm = segtr[ls].len + segtr[rs].lm;
    else
        segtr[p].lm = segtr[ls].lm;
    if (segtr[rs].mx == segtr[rs].len)
        segtr[p].rm = segtr[rs].len + segtr[ls].rm;
    else
        segtr[p].rm = segtr[rs].rm;
    segtr[p].mx = max(segtr[ls].mx, segtr[rs].mx, segtr[ls].rm + segtr[rs].lm);
}
void pushdown(int p)
{
    if (segtr[p].lazy == 0)
        return;
    if (segtr[p].lazy == 1)
    {
        segtr[ls].lazy = segtr[rs].lazy = 1;
        segtr[ls].mx = segtr[ls].lm = segtr[ls].rm = segtr[rs].mx = segtr[rs].lm = segtr[rs].rm = 0;
    }
    if (segtr[p].lazy == 2)
    {
        segtr[ls].lazy = segtr[rs].lazy = 2;
        segtr[ls].mx = segtr[ls].lm = segtr[ls].rm = segtr[ls].len;
        segtr[rs].mx = segtr[rs].lm = segtr[rs].rm = segtr[rs].len;
    }
    segtr[p].lazy = 0;
}

void modify(int p, int l, int r, const int op, const int ml, const int mr)
{
    pushdown(p);
    if (ml <= l && r <= mr)
    {
        if (op == 1)
            segtr[p].mx = segtr[p].lm = segtr[p].rm = 0;
        else
            segtr[p].mx = segtr[p].lm = segtr[p].rm = segtr[p].len;
        segtr[p].lazy = op;
        return;
    }

    int mid = (l + r) >> 1;
    if (ml <= mid)
        modify(ls, l, mid, op, ml, mr);
    if (mr > mid)
        modify(rs, mid + 1, r, op, ml, mr);
    pushup(p);
}
int query(int p, int l, int r, int n)
{
    if (l == r)
        return l;

    pushdown(p);
    int mid = (l + r) >> 1;
    if (segtr[ls].mx >= n)
        return query(ls, l, mid, n);
    else if (segtr[ls].rm + segtr[rs].lm >= n)
        return mid - segtr[ls].rm + 1;
    else
        return query(rs, mid + 1, r, n);
}

int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    build(1, 1, n);

    for (int i = 0, op, x, y; i < m; i++)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x;
            if (segtr[1].mx >= x)
            {
                int left = query(1, 1, n, x);
                cout << left << endl;
                modify(1, 1, n, 1, left, left + x - 1);
            }
            else
                cout << 0 << endl;
        }
        else
        {
            cin >> x >> y;
            modify(1, 1, n, 2, x, x + y - 1);
        }
    }
    return 0;
}
