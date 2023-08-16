#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, k, idx;
struct
{
    int ls, rs, val;
} t[N << 6];

void insert(int &p, int l, int r, int x)
{
    t[p = ++idx].val = 1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        insert(t[p].ls, l, mid, x);
    else
        insert(t[p].rs, mid + 1, r, x);
}
void split(int p, int &q, int k)
{
    if (!p)
        return q = 0, void();
    q = ++idx;
    if (t[t[p].ls].val > k)
        swap(t[p].rs, t[q].rs), split(t[p].ls, t[q].ls, k);
    else if (t[t[p].ls].val == k)
        swap(t[p].rs, t[q].rs);
    else
        split(t[p].rs, t[q].rs, k - t[t[p].ls].val);
    t[q].val = t[p].val - k, t[p].val = k;
}
void merge(int &p, int q)
{
    if (!p || !q)
        return p |= q, void();
    merge(t[p].ls, t[q].ls);
    merge(t[p].rs, t[q].rs);
    t[p].val += t[q].val;
}

struct tree
{
    int l, r, p, op;
    bool operator<(const tree &o) const { return l != o.l ? l < o.l : r < o.r; }
};
set<tree> s;
void split(int x)
{
    if (!x)
        return;
    auto o = --s.lower_bound({x + 1});
    if (o->r == x)
        return;
    int p = o->p, q = 0;
    if (!o->op)
        split(p, q, x - o->l + 1);
    else
        split(p, q, o->r - x), swap(p, q);
    s.insert({o->l, x, p, o->op}), s.insert({x + 1, o->r, q, o->op});
    s.erase(o);
}
int kth(int p, int l, int r, int k)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (k <= t[t[p].ls].val)
        return kth(t[p].ls, l, mid, k);
    else
        return kth(t[p].rs, mid + 1, r, k - t[t[p].ls].val);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x, r; i <= n; i++)
    {
        cin >> x, r = 0;
        insert(r, 1, n, x), s.insert({i, i, r, 0});
    }
    for (int i = 1, op, l, r; i <= m; i++)
    {
        cin >> op >> l >> r;
        split(l - 1), split(r);
        int p = 0;
        while (true)
        {
            auto o = s.lower_bound({l});
            if (o == s.end() || o->l > r)
                break;
            merge(p, o->p), s.erase(o);
        }
        s.insert({l, r, p, op});
    }
    cin >> k;
    auto o = --s.lower_bound({k + 1});
    cout << kth(o->p, 1, n, o->op ? o->r - k + 1 : k - o->l + 1);
    return 0;
}