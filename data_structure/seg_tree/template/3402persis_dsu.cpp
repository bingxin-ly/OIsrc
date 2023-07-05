#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5, M = 2e5 + 5;
struct
{
    int ls, rs, val, rnk;
} t[N * 2 + M * 40]; // 每次操作 1 会修改两次，一次修改父节点，一次修改父节点的秩
int n, m, idx, rt[M];

void build(int &p, int l, int r)
{
    p = ++idx;
    if (l == r)
        return t[p].val = l, t[p].rnk = 1, void();
    int mid = (l + r) >> 1;
    build(t[p].ls, l, mid), build(t[p].rs, mid + 1, r);
}
int rnk(int p, int l, int r, int pos)
{
    if (l == r)
        return t[p].rnk;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return rnk(t[p].ls, l, mid, pos);
    else
        return rnk(t[p].rs, mid + 1, r, pos);
}
void updrnk(int &p, int l, int r, int pos, int val)
{
    t[++idx] = t[p], p = idx;
    if (l == r)
        return t[p].rnk = max(t[p].rnk, val), void();
    int mid = (l + r) >> 1;
    if (pos <= mid)
        updrnk(t[p].ls, l, mid, pos, val);
    else
        updrnk(t[p].rs, mid + 1, r, pos, val);
}
int query(int p, int l, int r, int pos)
{
    if (l == r)
        return t[p].val;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return query(t[p].ls, l, mid, pos);
    else
        return query(t[p].rs, mid + 1, r, pos);
}
int find(int p, int pos)
{
    int f = query(p, 1, n, pos);
    return pos == f ? pos : find(p, f);
}
void modify(int &p, int l, int r, int pos, int fa)
{
    t[++idx] = t[p], p = idx;
    if (l == r)
        return t[p].val = fa, void();
    int mid = (l + r) >> 1;
    if (pos <= mid)
        modify(t[p].ls, l, mid, pos, fa);
    else
        modify(t[p].rs, mid + 1, r, pos, fa);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    build(rt[0], 1, n);

    for (int i = 1, op, a, b; i <= m; i++)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> a >> b;
            int fa = find(rt[i - 1], a), fb = find(rt[i - 1], b);
            if (fa == fb)
                rt[i] = rt[i - 1];
            else
            {
                if (rnk(rt[i - 1], 1, n, fa) > rnk(rt[i - 1], 1, n, fb))
                    swap(fa, fb);
                modify(rt[i] = rt[i - 1], 1, n, fa, fb);
                updrnk(rt[i], 1, n, fb, rnk(rt[i - 1], 1, n, fa) + 1);
            }
        }
        else if (op == 2)
            cin >> a, rt[i] = rt[a];
        else
        {
            cin >> a >> b;
            rt[i] = rt[i - 1];
            cout << (find(rt[i], a) == find(rt[i], b)) << '\n';
        }
    }
    return 0;
}