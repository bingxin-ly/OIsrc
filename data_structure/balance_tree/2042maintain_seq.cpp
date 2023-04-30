#include <bits/stdc++.h>
#define max(_a, _b) (((_a) > (_b)) ? (_a) : (_b))
using namespace std;

/* int read()
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
} */

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
};

void update(node *u)
{
    bool hasls = u->ls, hasrs = u->rs;

    u->size = (hasls ? u->ls->size : 0) + (hasrs ? u->rs->size : 0) + 1;
    u->sum = (hasls ? u->ls->sum : 0) + (hasrs ? u->rs->sum : 0) + u->val;
    u->lmax = max(hasls ? u->ls->lmax : ~0xffff, (hasls ? u->ls->sum : 0) + u->val + (hasrs ? u->rs->lmax : 0));
    u->rmax = max(hasrs ? u->rs->rmax : ~0xffff, (hasrs ? u->rs->sum : 0) + u->val + (hasls ? u->ls->rmax : 0));
    u->maxn = max(u->val, u->val + (hasls ? u->ls->rmax : 0) + (hasrs ? u->rs->lmax : 0));
    if (hasls)
        u->maxn = max(u->maxn, u->ls->maxn);
    if (hasrs)
        u->maxn = max(u->maxn, u->rs->maxn);
}

/* void reverse(node *u)
{
    swap(u->ls, u->rs);
    swap(u->rmax, u->lmax);
    u->reved ^= 1;
} */
void cover(node *u)
{
    u->sum = u->size * u->val;
    u->lmax = u->rmax = max(0, u->sum);
    u->maxn = max(u->val, u->sum);
    u->coved = true;
}
void pushdown(node *u)
{
    if (u->reved)
    {
        swap(u->ls, u->rs), swap(u->rmax, u->lmax);
        if (u->ls)
            // reverse(u->ls);
            u->ls->reved ^= 1;
        if (u->rs)
            // reverse(u->rs);
            u->rs->reved ^= 1;
        u->reved = false;
    }
    if (u->coved)
    {
        if (u->ls)
            u->ls->val = u->val,
            cover(u->ls);
        if (u->rs)
            u->rs->val = u->val,
            cover(u->rs);
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

// node *root = nullptr;
/* void build(int n)
{
    for (int i = 1, x; i <= n; i++)
        // x = read(),
        cin >> x,
        root = merge(root, new node(x));
} */

void delnode(node *u)
{
    if (!u)
        return;
    delnode(u->ls), delnode(u->rs);
    delete u;
}

void inorder(node *u)
{
    if (!u)
        return;
    pushdown(u);
    inorder(u->ls);
    printf("At val %d: \nls: %d, rs: %d, lmax: %d, rmax: %d, maxn: %d\n", 
    u->val, u->ls ? u->ls->val : 0, u->rs ? u->rs->val : 0,
    u->lmax, u->rmax, u->maxn);
    inorder(u->rs);
}

node *root, *p, *L, *R;
int main()
{
    freopen("./0.in", "r", stdin);

    // int n = read(), m = read();
    int n, m;
    cin >> n >> m;
    // build(n);
    for (int i = 1, x; i <= n; i++)
    // x = read(),
        cin >> x,
        root = merge(root, new node(x));

    while (m--)
    {
        int pos, tot;
        char opt[10];
        cin >> opt;
        if (opt[2] != 'X')
            // pos = read(), tot = read();
            cin >> pos >> tot;
        switch (opt[2])
        {
        case 'S':
            split(root, pos, L, R);
            for (int i = 1, x; i <= tot; i++)
                // x = read(),
                cin >> x,
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
            cin >> p->val,
            /* p->val = read(), */ p->coved = true;
            root = merge(merge(L, p), R);
            break;
        case 'V':
            split(root, pos - 1 + tot, L, R), split(L, pos - 1, L, p);
            // inorder(L), printf(" "), inorder(p), printf(" "), inorder(R);
            p->reved ^= 1;
            // reverse(p);
            // inorder(p);
            root = merge(merge(L, p), R);
            break;
        case 'T':
            split(root, pos - 1 + tot, L, R), split(L, pos - 1, L, p);
            printf("%d\n", p->sum);
            root = merge(merge(L, p), R);
            break;
        case 'X':
            inorder(p);
            printf("\n%d\n", root->maxn);
            break;
        }
        puts(opt), inorder(root), puts("");
    }
    return 0;
}
