#include <bits/stdc++.h>
#define ls rt << 1
#define rs rt << 1 | 1
using namespace std;
int max(int a, int b, int c) { return max(max(a, b), c); }

const int MAX = 5e5 + 10;

struct node
{
    int lm, rm, max, len;
    int lazy;
} segtr[4 * MAX];

void build(int rt, int l, int r)
{
    segtr[rt].lm = segtr[rt].rm = segtr[rt].max = segtr[rt].len = r - l + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
}
void pushup(int rt)
{
    if (segtr[ls].max == segtr[ls].len)
        segtr[rt].lm = segtr[ls].len + segtr[rs].lm;
    else
        segtr[rt].lm = segtr[ls].lm;
    if (segtr[rs].max == segtr[rs].len)
        segtr[rt].rm = segtr[rs].len + segtr[ls].rm;
    else
        segtr[rt].rm = segtr[rs].rm;
    segtr[rt].max = max(segtr[ls].max, segtr[rs].max, segtr[ls].rm + segtr[rs].lm);
                            // 两个子树的max比较你个傻x
}
void pushdown(int rt)
{
    if (segtr[rt].lazy == 0)
        return;
    if (segtr[rt].lazy == 1)
    {
        segtr[ls].lazy = segtr[rs].lazy = 1;
        segtr[ls].max = segtr[ls].lm = segtr[ls].rm = segtr[rs].max = segtr[rs].lm = segtr[rs].rm = 0;
    }
    if (segtr[rt].lazy == 2)
    {
        segtr[ls].lazy = segtr[rs].lazy = 2;
        segtr[ls].max = segtr[ls].lm = segtr[ls].rm = segtr[ls].len;
        segtr[rs].max = segtr[rs].lm = segtr[rs].rm = segtr[rs].len;
    }
    segtr[rt].lazy = 0;
}
// 别抄别人代码函数顺序都抄不对你个傻x
void modify(int rt, int l, int r, const int op, const int ml, const int mr)
{
    // if (ml > r || mr < l) return;
    pushdown(rt);
    if (ml <= l && r <= mr)
    {
        if (op == 1)
            segtr[rt].max = segtr[rt].lm = segtr[rt].rm = 0;
        else 
            segtr[rt].max = segtr[rt].lm = segtr[rt].rm = segtr[rt].len;
        segtr[rt].lazy = op;
        return;
    }

    int mid = (l + r) >> 1;
    if (ml <= mid)
        modify(ls, l, mid, op, ml, mr);
    if (mr > mid)
        modify(rs, mid + 1, r, op, ml, mr);
    pushup(rt);
}
int query(int rt, int l, int r, int n)
{
    pushdown(rt);
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (segtr[ls].max >= n)
        return query(ls, l, mid, n); // 完全在左子树中查找
    if (segtr[ls].rm + segtr[rs].lm >= n)
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
            if (segtr[1].max >= x)
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
