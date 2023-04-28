#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int cnt;
struct node
{
    int ls, rs;
    int key, pri;
    int size;
} t[N];

void new_node(int x)
{
    cnt++;
    t[cnt].size = 1;
    t[cnt].ls = t[cnt].rs = 0;
    t[cnt].key = x;
    t[cnt].pri = rand();
}

void update(int u)
{
    t[u].size = t[t[u].ls].size + t[t[u].rs].size + 1;
}

void rotate(int &o, int d)
{
    int k;
    if (d == 1)
    {
        k = t[o].rs;
        t[o].rs = t[k].ls;
        t[k].ls = o;
    }
    else
    {
        k = t[o].ls;
        t[o].ls = t[k].rs;
        t[k].rs = o;
    }
    t[k].size = t[o].size;
    update(o);
    o = k;
}

void insert(int &u, int x)
{
    if (u == 0)
    {
        new_node(x);
        u = cnt;
        return;
    }
    t[u].size++;
    if (x >= t[u].key)
        insert(t[u].rs, x);
    else
        insert(t[u].ls, x);
    if (t[u].ls && t[u].pri > t[t[u].ls].pri)
        rotate(u, 0);
    if (t[u].rs && t[u].pri > t[t[u].rs].pri)
        rotate(u, 1);
    update(u);
}

void del(int &u, int x)
{
    t[u].size--;
    if (t[u].key == x)
    {
        if (!t[u].ls && !t[u].rs)
            return u = 0, void();
        if (!t[u].ls || !t[u].rs)
        {
            u = t[u].ls + t[u].rs;
            return;
        }
        if (t[t[u].ls].pri < t[t[u].rs].pri)
        {
            rotate(u, 0);
            del(t[u].rs, x);
            return;
        }
        else
        {
            rotate(u, 1);
            del(t[u].ls, x);
            return;
        }
    }
    if (t[u].key >= x)
        del(t[u].ls, x);
    else
        del(t[u].rs, x);
    update(u);
}

int rnk(int u, int x)
{
    if (!u)
        return 0;
    if (x > t[u].key)
        return t[t[u].ls].size + 1 + rnk(t[u].rs, x);
    return rnk(t[u].ls, x);
}

int kth(int u, int x)
{
    if (x == t[t[u].ls].size + 1)
        return t[u].key;
    if (x > t[t[u].ls].size + 1)
        return kth(t[u].rs, x - t[t[u].ls].size - 1);
    if (x <= t[t[u].ls].size)
        kth(t[u].ls, x);
}

int precursor(int u, int x)
{
    if (!u)
        return 0;
    if (t[u].key >= x)
        return precursor(t[u].ls, x);
    int tmp = precursor(t[u].rs, x);
    return tmp ? tmp : t[u].key;
}

int successor(int u, int x)
{
    if (!u)
        return 0;
    if (t[u].key <= x)
        return successor(t[u].rs, x);
    int tmp = successor(t[u].ls, x);
    return tmp ? tmp : t[u].key;
}

int main()
{
    int n, rt = 0;
    cin >> n;
    while (n--)
    {
        int opt, x;
        cin >> opt >> x;
        switch (opt)
        {
        case 1:
            insert(rt, x);
            break;
        case 2:
            del(rt, x);
            break;
        case 3:
            cout << rnk(rt, x) + 1 << endl;
            break;
        case 4:
            cout << kth(rt, x) << endl;
            break;
        case 5:
            cout << precursor(rt, x) << endl;
            break;
        case 6:
            cout << successor(rt, x) << endl;
            break;
        }
    }
    return 0;
}