#include <bits/stdc++.h>
#define max(_a, _b) (((_a) > (_b)) ? (_a) : (_b))
using namespace std;

int read()
{
    int o = 1, p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            o = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0',
        c = getchar();
    return o * p;
}

struct node
{
    node *ls, *rs;
    int val, pri, size;
    int sum, maxn, lmax, rmax;
    bool reved, coved;

    explicit node(int x) : size(1)
    {
        ls = rs = nullptr;
        pri = rand();
        reved = coved = false;
        val = sum = maxn = x;
        lmax = rmax = max(x, 0);
    }
} *root;

void update(node *u)
{
    u->size = (u->ls ? u->ls->size : 0) + (u->rs ? u->rs->size : 0) + 1;
    u->sum = (u->ls ? u->ls->sum : 0) + (u->rs ? u->rs->sum : 0) + u->val;

    u->lmax = max(max(u->ls ? u->ls->lmax : ~0xffff, (u->ls ? u->ls->sum : 0) + u->val + (u->rs ? u->rs->lmax : 0)), 0);
    u->rmax = max(max(u->rs ? u->rs->rmax : ~0xffff, (u->rs ? u->rs->sum : 0) + u->val + (u->ls ? u->ls->rmax : 0)), 0);
    u->maxn = max(u->val, u->val + (u->ls ? u->ls->rmax : 0) + (u->rs ? u->rs->lmax : 0));
    if (u->ls)
        u->maxn = max(u->maxn, u->ls->maxn);
    if (u->rs)
        u->maxn = max(u->maxn, u->rs->maxn);
}

void reverse(node *u)
{
    swap(u->ls, u->rs);
    swap(u->rmax, u->lmax);
    u->reved ^= 1;
}
void cover(node *u, int x)
{
    u->val = x;
    u->sum = u->size * x;
    u->lmax = u->rmax = max(0, u->sum);
    u->maxn = max(x, u->sum);
    u->coved = true;
}
void pushdown(node *u)
{
    if (u->reved)
    {
        if (u->ls)
            reverse(u->ls);
        if (u->rs)
            reverse(u->rs);
        u->reved = false;
    }
    if (u->coved)
    {
        if (u->ls)
            // u->ls->val = u->val,
            cover(u->ls, u->val);
        if (u->rs)
            // u->rs->val = u->val,
            cover(u->rs, u->val);
        u->coved = false;
    }
}

// 排名分裂
void split(node *u, int x, node *&L, node *&R)
{
    if (!u)
        return L = R = nullptr, void();
    pushdown(u);
    int less = (u->ls ? u->ls->size : 0) + 1;
    if (x >= less)
    {
        L = u;
        split(u->rs, x - less, u->rs, R);
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
        pushdown(L);
        L->rs = merge(L->rs, R);
        update(L);
        return L;
    }
    else
    {
        pushdown(R);
        R->ls = merge(L, R->ls);
        update(R);
        return R;
    }
}

void delnode(node *u)
{
    if (!u)
        return;
    delnode(u->ls), delnode(u->rs);
    delete u;
}

int main()
{
    int n = read(), m = read();
    for (int i = 1, x; i <= n; i++)
        x = read(),
        root = merge(root, new node(x));

    node *p, *L, *R;
    while (m--)
    {
        int pos, tot;
        char opt[10];
        cin >> opt;
        if (opt[2] != 'X')
            pos = read(), tot = read();
        switch (opt[2])
        {
        case 'S':
            split(root, pos, L, R);
            for (int i = 1, x; i <= tot; i++)
                x = read(),
                L = merge(L, new node(x));
            root = merge(L, R);
            break;
        case 'L':
            split(root, pos - 1 + tot, L, R), split(L, pos - 1, L, p);
            delnode(p);
            root = merge(L, R);
            break;
        case 'K':
            split(root, pos - 1 + tot, L, R), split(L, pos - 1, L, p);
            cin >> p->val, cover(p, p->val);
            root = merge(merge(L, p), R);
            break;
        case 'V':
            split(root, pos - 1 + tot, L, R), split(L, pos - 1, L, p);
            reverse(p);
            root = merge(merge(L, p), R);
            break;
        case 'T':
            split(root, pos - 1 + tot, L, R), split(L, pos - 1, L, p);
            printf("%d\n", p ? p->sum : 0);
            root = merge(merge(L, p), R);
            break;
        case 'X':
            printf("%d\n", root->maxn);
            break;
        }
    }
    return 0;
}
