#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, INF = INT_MAX;
struct node
{
    node *ls, *rs;
    int key, val;
    int size;
} tr[N];
void update(int rt)
{
    tr[rt].size = tr[rt].ls->size + tr[rt].rs->size + 1;
}

// Zig(左旋)——Zag(右旋)
void zig(node &*rt)
{
    node *k = tr[rt].rs;
    tr[rt].rs = k->ls;
    k->ls = &(tr[rt]);
    k->size = tr[rt].size;
    update(rt);
    rt = k;
}
void zag(int &rt)
{
    node *k = tr[rt].ls;
    tr[rt].ls = k->rs;
    k->rs = rt;
    k->size = tr[rt].size;
    update(rt);
    rt = k;
}
int main()
{
    return 0;
}