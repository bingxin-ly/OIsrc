#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5,
          K = N * 50; // 复杂度是对的，但由于我没写空间回收，导致出现这样的情况
int idx, val[K], ls[K], rs[K];

void split(int p, int &q, int k)
{
    if (!p)
        return q = 0, void();
    q = ++idx;
    if (k < val[ls[p]])
        swap(rs[p], rs[q]), split(ls[p], ls[q], k);
    else if (k == val[ls[p]])
        swap(rs[p], rs[q]);
    else
        split(rs[p], rs[q], k - val[ls[p]]);
    val[q] = val[p] - k, val[p] = k;
}
int merge(int p, int q)
{
    if (!p || !q)
        return p | q;
    ls[p] = merge(ls[p], ls[q]);
    rs[p] = merge(rs[p], rs[q]);
    val[p] += val[q];
    return p;
}
void insert(int &p, int l, int r, int x)
{
    val[p = ++idx] = 1;
    if (l == r)
        return;
    int m = (l + r) >> 1;
    if (x <= m)
        insert(ls[p], l, m, x);
    else
        insert(rs[p], m + 1, r, x);
}
int kth(int p, int l, int r, int k)
{
    if (l == r)
        return l;
    int m = (l + r) >> 1;
    if (k <= val[ls[p]])
        return kth(ls[p], l, m, k);
    else
        return kth(rs[p], m + 1, r, k - val[ls[p]]);
}
struct dat
{
    int l, r, tp, rt;
    bool operator<(const dat &o) const { return l < o.l || (!(o.l < l) && r < o.r); }
};
set<dat> s;
void split(int x)
{
    if (!x)
        return;
    auto it = --s.lower_bound({x + 1});
    if (it->r == x)
        return;
    int p = it->rt, q = 0;
    if (!it->tp)
        split(p, q, x - it->l + 1);
    else
        split(p, q, it->r - x), swap(p, q);
    s.insert({it->l, x, it->tp, p}), s.insert({x + 1, it->r, it->tp, q});
    s.erase(it);
}
void operate(int l, int r, int tp)
{
    split(l - 1), split(r);
    int rt = 0;
    while (true)
    {
        auto it = s.lower_bound({l});
        if (it == s.end() || it->l > r)
            break;
        rt = merge(rt, it->rt);
        s.erase(it);
    }
    s.insert({l, r, tp, rt});
}

int n, m;
int query(int pos)
{
    auto it = --s.lower_bound({pos + 1});
    int rnk = !it->tp ? pos - it->l + 1 : it->r - pos + 1;
    return kth(it->rt, 1, n, rnk);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int x, rt = 0;
        cin >> x, insert(rt, 1, n, x);
        s.insert({i, i, 0, rt});
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r, tp;
        cin >> tp >> l >> r;
        operate(l, r, tp);
    }
    int k;
    cin >> k;
    cout << query(k);
    return 0;
}