// 排名树，FHQ实现 P4008文本编辑器
#include <bits/stdc++.h>
using namespace std;

struct node
{
    node *ls, *rs;
    int num, pri, size;
    int lazy;

    explicit node(char x) : num(x), size(1)
    {
        ls = rs = nullptr;
        pri = rand();
    }

    int lssz() const { return ls ? ls->size : 0; }
    int rssz() const { return rs ? rs->size : 0; }
    int lslz() const { return ls ? ls->lazy : 0; }
    int rslz() const { return rs ? rs->lazy : 0; }
} *root;

void update(node *u)
{
    u->size = u->lssz() + u->rssz() + 1;
}
void pushdown(node *u)
{
    if (u->lazy)
    {
        swap(u->ls, u->rs);
        u->ls->lazy ^= 1, u->rs->lazy ^= 1;
        u->lazy = 0;
    }
}

// 排名分裂
void split(node *u, int x, node *&L, node *&R)
{
    if (!u)
        return L = R = nullptr, void();
    pushdown(u);
    int less = u->lssz() + 1;
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

void inorder(node *u)
{
    if (!u)
        return;
    pushdown(u);
    inorder(u->ls);
    printf("%c ", u->num);
    inorder(u->rs);
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        root = merge(root, new node(i));
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        node *L, *R, *p;
        split(root, y, L, R);
        split(L, x - 1, L, p);
        p->lazy ^= 1;
        root = merge(merge(L, p), R);
    }
    inorder(root);
    return 0;
}