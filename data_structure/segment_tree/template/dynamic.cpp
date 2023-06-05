#include <bits/stdc++.h>
using namespace std;

class segment_tree
{
    struct node
    {
        node *ls, *rs;
        int l, r, // 维护的左、右端点
            val, lazy;
        node(int l_, int r_) : l(l_), r(r_)
        {
            val = lazy = 0;
            ls = rs = nullptr;
        }
    } *root;

    static void pushup(node *p)
    {
        p->val = (p->ls ? p->ls->val : 0) + (p->rs ? p->rs->val : 0);
    }
    static void pushdown(node *p)
    {
        if (p->lazy)
        {
            int mid = (p->l + p->r) >> 1;
            p->ls->val += (mid - p->l + 1) * p->lazy;
            p->rs->val += (p->r - mid) * p->lazy;

            p->ls->lazy += p->lazy, p->rs->lazy += p->lazy;
            p->lazy = 0;
        }
    }

    void build(node *&p, int l, int r, const int *arr)
    {
        p = new node(l, r);
        if (l == r)
            return p->val = arr[l], void();

        int mid = (l + r) >> 1;
        build(p->ls, l, mid, arr), build(p->rs, mid + 1, r, arr);
        pushup(p);
    }

    void update(node *p, int l, int r, int v)
    {
        if (l <= p->l && p->r <= r)
        {
            p->val += (p->r - p->l + 1) * v;
            p->lazy += v;
            return;
        }

        pushdown(p);
        int mid = (p->l + p->r) >> 1;
        if (l <= mid)
        {
            if (!p->ls)
                p->ls = new node(p->l, mid);
            update(p->ls, l, r, v);
        }
        if (r > mid)
        {
            if (!p->rs)
                p->rs = new node(mid + 1, p->r);
            update(p->rs, l, r, v);
        }
        pushup(p);
    }

    int query(node *p, int l, int r)
    {
        if (!p)
            return 0;
        if (l <= p->l && p->r <= r)
            return p->val;

        pushdown(p);
        int mid = (p->l + p->r) >> 1;
        int res = 0;
        if (l <= mid)
            res += query(p->ls, l, r);
        if (r > mid)
            res += query(p->rs, l, r);
        return res;
    }

public:
    void build(int n, const int *arr) { build(root, 1, n, arr); }
    void update(int l, int r, int v) { update(root, l, r, v); }
    int query(int l, int r) { return query(root, l, r); }
} segtr;

signed main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int arr[n + 1];
    for (int i = 1; i <= n; i++)
        scanf("%d", arr + i);
    segtr.build(n, arr);

    for (int op, x, y, k; m--;)
    {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1)
            scanf("%d", &k), segtr.update(x, y, k);
        else
            printf("%d\n", segtr.query(x, y));
    }
    return 0;
}