// 使用 FHQ 实现权值树（Treap）
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int cnt, root;
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

// 权值分裂
void split(int u, int x, int &L, int &R)
{
    if (!u)
        return L = R = 0, void();
    if (t[u].key <= x)
    {
        L = u;
        split(t[u].rs, x, t[u].rs, R);
    }
    else
    {
        R = u;
        split(t[u].ls, x, L, t[u].ls);
    }
    update(u);
}

int merge(int L, int R)
{
    if (!L || !R)
        return L + R;
    if (t[L].pri > t[R].pri)
    {
        t[L].rs = merge(t[L].rs, R);
        update(L);
        return L;
    }
    else
    {
        t[R].ls = merge(L, t[R].ls);
        update(R);
        return R;
    }
}

int insert(int x)
{
    int L, R;
    split(root, x, L, R);
    new_node(x);
    root = merge(merge(L, cnt), R);
}

int del(int x)
{
    int L, R, p;
    split(root, x, L, R);
    split(L, x - 1, L, p);
    p = merge(t[p].ls, t[p].rs);
    root = merge(merge(L, p), R);
}

int rnk(int x)
{
    int L, R;
    split(root, x - 1, L, R);
    root = merge(L, R);
    return t[L].size + 1;
}

int kth(int u, int k)
{
    int less = t[t[u].ls].size + 1;
    if (k == less)
        return u;
    if (k < less)
        return kth(t[u].ls, k);
    if (k > less)
        return kth(t[u].rs, k - less);
}

int precursor(int x)
{
    
}