#include <bits/stdc++.h>
using namespace std;

class Treap
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
        int lssize() { return ls ? ls->size : 0; }
        int rssize() { return rs ? rs->size : 0; }
    };

    void update(node *&u)
    {
        // u->size = 1;
        // u->size += u->ls ? u->ls->size : 0;
        // u->size += u->rs ? u->rs->size : 0;
        u->size = u->lssize() + u->rssize() + 1;
    }

    void rotate(node *&o, int d)
    {
        node *k;
        if (d == 1)
        {
            k = o->rs;
            o->rs = k->ls;
            k->ls = o;
        }
        else
        {
            k = o->ls;
            o->ls = k->rs;
            k->rs = o;
        }
        k->size = o->size;
        update(o);
        o = k;
    }

public:
    node *rt;
    void insert(node *&u, int x)
    {
        if (u == 0)
        {
            u = new node(x);
            return;
        }
        u->size++;
        if (x >= u->key)
            insert(u->rs, x);
        else
            insert(u->ls, x);
        if (u->ls && u->pri > u->ls->pri)
            rotate(u, 0);
        if (u->rs && u->pri > u->rs->pri)
            rotate(u, 1);
        update(u);
    }

    void del(node *&u, int x)
    {
        u->size--;
        if (u->key == x)
        {
            if (!u->ls && !u->rs)
                return delete u, u = nullptr, void();
            if (!u->ls || !u->rs)
            {
                u = u->ls ? u->ls : u->rs;
                return;
            }
            if (u->ls->pri < u->rs->pri)
            {
                rotate(u, 0);
                del(u->rs, x);
                return;
            }
            else
            {
                rotate(u, 1);
                del(u->ls, x);
                return;
            }
        }
        if (u->key >= x)
            del(u->ls, x);
        else
            del(u->rs, x);
        update(u);
    }

    int rnk(node *u, int x)
    {
        if (!u)
            return 0;
        if (x > u->key)
            return u->lssize() + 1 + rnk(u->rs, x);
        return rnk(u->ls, x);
    }

    int kth(node *u, int x)
    {
        int less = u->lssize() + 1;
        if (x == less)
            return u->key;
        if (x > less)
            return kth(u->rs, x - less);
        if (x < less)
            kth(u->ls, x);
    }

    int precursor(node *u, int x)
    {
        if (!u)
            return 0;
        if (u->key >= x)
            return precursor(u->ls, x);
        int tmp = precursor(u->rs, x);
        return tmp ? tmp : u->key;
    }

    int successor(node *u, int x)
    {
        if (!u)
            return 0;
        if (u->key <= x)
            return successor(u->rs, x);
        int tmp = successor(u->ls, x);
        return tmp ? tmp : u->key;
    }
} tr;

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
            tr.insert(tr.rt, x);
            break;
        case 2:
            tr.del(tr.rt, x);
            break;
        case 3:
            cout << tr.rnk(tr.rt, x) + 1 << endl;
            break;
        case 4:
            cout << tr.kth(tr.rt, x) << endl;
            break;
        case 5:
            cout << tr.precursor(tr.rt, x) << endl;
            break;
        case 6:
            cout << tr.successor(tr.rt, x) << endl;
            break;
        }
    }
    return 0;
}