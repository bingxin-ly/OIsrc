#include <bits/stdc++.h>
using namespace std;

class FHQ_tree
{
    struct node
    {
        node *ls, *rs;
        int val, size, pri;

        explicit node(int x) : val(x), size(1)
        {
            ls = rs = nullptr;
            pri = rand();
        }
    } *root = nullptr;

    static inline void update(node *u)
    {
        u->size = (u->ls ? u->ls->size : 0) + (u->rs ? u->rs->size : 0) + 1;
    }

    // 权值分裂
    void split(node *u, int x, node *&L, node *&R)
    {
        if (!u)
            return L = R = nullptr, void();
        if (u->val <= x)
        {
            L = u;
            split(u->rs, x, u->rs, R);
        }
        else
        {
            R = u;
            split(u->ls, x, L, u->ls);
        }
        update(u);
    }

    node *merge(node *L, node *R)
    {
        if (!L || !R)
            return L ? L : R;
        if (L->pri > R->pri)
        {
            L->rs = merge(L->rs, R);
            update(L);
            return L;
        }
        else
        {
            R->ls = merge(L, R->ls);
            update(R);
            return R;
        }
    }

public:
    void insert(int x)
    {
        node *L, *R;
        split(root, x, L, R);
        root = merge(merge(L, new node(x)), R);
    }

    void del(int x)
    {
        node *L, *R, *p;
        split(root, x, L, R);
        split(L, x - 1, L, p);
        p = merge(p->ls, p->rs);
        root = merge(merge(L, p), R);
    }

    int rnk(int x)
    {
        node *L, *R;
        split(root, x - 1, L, R);
        int ret = L ? L->size : 0;
        root = merge(L, R);
        return ret;
    }

    int kth(node *u, int k)
    {
        int less = (u->ls ? u->ls->size : 0) + 1;
        if (k == less)
            return u->val;
        else if (k < less)
            return kth(u->ls, k);
        else /* if (k > less) */
            return kth(u->rs, k - less);
    }

    int precursor(int x)
    {
        node *L, *R;
        split(root, x - 1, L, R);
        if (!L)
            return -INT_MAX;
        int ans = kth(L, L->size);
        root = merge(L, R);
        return ans;
    }

    int succssor(int x)
    {
        node *L, *R;
        split(root, x, L, R);
        if (!R)
            return INT_MAX;
        int ans = kth(R, 1);
        root = merge(L, R);
        return ans;
    }
};

int src[50010];
namespace SEGTR
{
    struct node
    {
        node *ls, *rs;
        int l, r;
        FHQ_tree val;

        node(int l_, int r_) : l(l_), r(r_)
        {
            val = FHQ_tree();
            ls = rs = nullptr;
        }
    } *root = nullptr;

    void build(node *&p, int l, int r)
    {
        p = new node(l, r);
        for (int i = l; i <= r; i++)
            p->val.insert(src[i]);
        if (l != r)
        {
            int mid = (l + r) >> 1;
            build(p->ls, l, mid), build(p->rs, mid + 1, r);
        }
    }
    void modify(node *p, int pos, int v)
    {
        p->val.del(src[pos]), p->val.insert(v);
        if (p->l == p->r)
            return;

        int mid = (p->l + p->r) >> 1;
        if (pos <= mid)
            modify(p->ls, pos, v);
        else
            modify(p->rs, pos, v);
    }

    int qrnk(node *p, int ql, int qr, int k)
    {
        if (p->l > qr || p->r < ql)
            return 0;
        if (ql <= p->l && p->r <= qr)
            return p->val.rnk(k);
        else
            return qrnk(p->ls, ql, qr, k) + qrnk(p->rs, ql, qr, k);
    }
    int qkth(int ql, int qr, int k)
    {
        int l = 0, r = 1e8;
        while (l < r)
        {
            int mid = (l + r + 1) >> 1, res = qrnk(root, ql, qr, mid);
            if (res < k)
                l = mid;
            else
                r = mid - 1;
        }
        return r;
    }
    int qpre(node *p, int ql, int qr, int k)
    {
        if (p->l > qr || p->r < ql)
            return -INT_MAX;
        if (ql <= p->l && p->r <= qr)
            return p->val.precursor(k);
        else
            return max(qpre(p->ls, ql, qr, k), qpre(p->rs, ql, qr, k));
    }
    int qsuc(node *p, int ql, int qr, int k)
    {
        if (p->l > qr || p->r < ql)
            return INT_MAX;
        if (ql <= p->l && p->r <= qr)
            return p->val.succssor(k);
        else
            return min(qsuc(p->ls, ql, qr, k), qsuc(p->rs, ql, qr, k));
    }
}
using SEGTR::root;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> src[i];
    SEGTR::build(root, 1, n);

    for (int opt, l, r, k; m--;)
    {
        cin >> opt >> l >> r;
        if (opt != 3)
            cin >> k;

        switch (opt)
        {
        case 1:
            cout << SEGTR::qrnk(root, l, r, k) + 1 << '\n';
            break;
        case 2:
            cout << SEGTR::qkth(l, r, k) << '\n';
            break;
        case 3:
            SEGTR::modify(root, l, r), src[l] = r;
            break;
        case 4:
            cout << SEGTR::qpre(root, l, r, k) << '\n';
            break;
        case 5:
            cout << SEGTR::qsuc(root, l, r, k) << '\n';
            break;
        }
    }
    return 0;
}