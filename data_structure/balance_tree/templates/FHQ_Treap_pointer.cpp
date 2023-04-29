// 使用 FHQ 实现权值树（Treap）
#include <bits/stdc++.h>
using namespace std;

class FHQ
{
    struct node
    {
        node *ls, *rs;
        int key, pri;
        int size;

        node(int x) : key(x), size(1)
        {
            ls = rs = nullptr;
            pri = rand();
        }

        int lssz() { return ls ? ls->size : 0; }
        int rssz() { return rs ? rs->size : 0; }
    };

    void update(node *u)
    {
        u->size = u->lssz() + u->rssz() + 1;
    }

    // 权值分裂
    void split(node *u, int x, node *&L, node *&R)
    {
        if (!u)
            return L = R = nullptr, void();
        if (u->key <= x)
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
    node *root;
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
        int ans = (L ? L->size : 0) + 1;
        root = merge(L, R);
        return ans;
    }

    int kth(node *u, int k)
    {
        int less = u->lssz() + 1;
        if (k == less)
            return u->key;
        if (k < less)
            return kth(u->ls, k);
        if (k > less)
            return kth(u->rs, k - less);
    }

    int precursor(int x)
    {
        node *L, *R;
        split(root, x - 1, L, R);
        int ans = kth(L, L ? L->size : 0);
        root = merge(L, R);
        return ans;
    }

    int succssor(int x)
    {
        node *L, *R;
        split(root, x, L, R);
        int ans = kth(R, 1);
        root = merge(L, R);
        return ans;
    }
} fhq;

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int opt, x;
        cin >> opt >> x;
        switch (opt)
        {
        case 1:
            fhq.insert(x);
            break;
        case 2:
            fhq.del(x);
            break;
        case 3:
            cout << fhq.rnk(x) << endl;
            break;
        case 4:
            cout << fhq.kth(fhq.root, x) << endl;
            break;
        case 5:
            cout << fhq.precursor(x) << endl;
            break;
        case 6:
            cout << fhq.succssor(x) << endl;
            break;
        }
    }
    return 0;
}
