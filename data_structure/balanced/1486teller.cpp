#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

int minn, leave, delta;
struct node
{
    node *ls, *rs;
    int val, pri, size;

    node(int x) : val(x), size(1)
    {
        ls = rs = nullptr;
        pri = rand();
    }
} *root;

void update(node *u)
{
    u->size = (u->ls ? u->ls->size : 0) + (u->rs ? u->rs->size : 0) + 1;
}

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

void insert(int x)
{
    node *L, *R;
    split(root, x, L, R);
    root = merge(merge(L, new node(x)), R);
}

int kth(node *u, int k)
{
    int bigger = (u->rs ? u->rs->size : 0) + 1;
    if (k == bigger)
        return u->val;
    if (k < bigger)
        return kth(u->rs, k);
    if (k > bigger)
        return kth(u->ls, k - bigger);
}

int main()
{
    int n = read();
    minn = read();
    while (n--)
    {
        char x;
        scanf("%s", &x);
        int k = read();
        switch (x)
        {
        case 'I':
            if (k < minn)
                continue;
            insert(k + delta);
            break;
        case 'A':
            delta -= k;
            break;
        case 'S':
            delta += k;
            node *L, *R;
            split(root, minn + delta - 1, L, R);
            leave += L ? L->size : 0, root = R;
            break;
        case 'F':
            printf("%d\n", k > (root ? root->size : 0) ? -1 : kth(root, k) - delta);
            break;
        }
    }
    printf("%d", leave);
    return 0;
}