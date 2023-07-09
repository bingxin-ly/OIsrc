#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\.in");
ofstream fout("D:\\OIsrc\\.out");
#define cin fin
#define cout fout
#undef endl
#endif

constexpr int N = 1e5 + 5;
int rnk[N], rid[N], fa[N];
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

struct
{
    int ls, rs, val;
} t[N * 100];
int idx, rt[N];
void pushup(int p) { t[p].val = t[t[p].ls].val + t[t[p].rs].val; }
void change(int &p, int l, int r, int pos)
{
    !p && (p = ++idx);
    if (l == r)
        return t[p].val += 1, void();
    int mid = (l + r) >> 1;
    if (pos <= mid)
        change(t[p].ls, l, mid, pos);
    else
        change(t[p].rs, mid + 1, r, pos);
    pushup(p);
}
void merge(int &p, int q, int l, int r)
{
    if (!p || !q)
        return p |= q, void();
    if (l == r)
        return t[p].val += t[q].val, void();
    int mid = (l + r) >> 1;
    merge(t[p].ls, t[q].ls, l, mid);
    merge(t[p].rs, t[q].rs, mid + 1, r);
    pushup(p);
}
int kth(int p, int k, int l, int r)
{
    if (!p)
        return -1;
    if (l == r)
        return l;
    int cnt = t[t[p].ls].val, mid = (l + r) >> 1;
    if (k <= cnt)
        return kth(t[p].ls, k, l, mid);
    else
        return kth(t[p].rs, k - cnt, mid + 1, r);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    iota(fa + 1, fa + n + 1, 1);
    for (int i = 1; i <= n; i++)
        cin >> rnk[i], rid[rnk[i]] = i, change(rt[i], 1, n, rnk[i]);
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        int fu = find(u), fv = find(v);
        if (fu != fv)
            merge(rt[fu], rt[fv], 1, n), fa[fv] = fu;
    }
    int q, x, y;
    cin >> q;
    char op;
    while (q--)
    {
        cin >> op >> x >> y;
        if (op == 'B')
        {
            int fx = find(x), fy = find(y);
            if (fx != fy)
                merge(rt[fx], rt[fy], 1, n), fa[fy] = fx;
        }
        else
        {
            int res = kth(rt[find(x)], y, 1, n);
            cout << (res != -1 ? rid[res] : res) << endl;
        }
    }
    return 0;
}