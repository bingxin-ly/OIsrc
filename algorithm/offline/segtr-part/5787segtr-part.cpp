#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\output\\.in");
ofstream fout("D:\\OIsrc\\output\\.out");
#define cin fin
#define cout fout
#endif

constexpr int N = 1e5 + 5, M = 2e5 + 5;
int n, m, k, u[M], v[M];
vector<int> t[N << 2];

int fa[N << 1], hi[N << 1];
stack<pair<int, int>> stk;
inline int find(int x)
{
    while (x != fa[x])
        x = fa[x];
    return x;
}
void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (hi[x] > hi[y])
        swap(x, y);
    stk.emplace(x, hi[x] == hi[y]);
    fa[x] = y, hi[y] += hi[x] == hi[y];
}

#define ls (p << 1)
#define rs (p << 1 | 1)
void insert(int p, int l, int r, int ql, int qr, int v)
{
    if (ql <= l && r <= qr)
        return t[p].emplace_back(v), void();
    int mid = (l + r) >> 1;
    if (ql <= mid)
        insert(ls, l, mid, ql, qr, v);
    if (qr > mid)
        insert(rs, mid + 1, r, ql, qr, v);
}
void solve(int p, int l, int r)
{
    bool ok = true;
    size_t s = stk.size();
    for (int i : t[p])
    {
        int fx = find(u[i]), fy = find(v[i]);
        if (fx == fy)
        {
            for (int k = l; k <= r; k++)
                cout << "No\n";
            ok = false;
            break;
        }
        merge(u[i], v[i] + n);
        merge(v[i], u[i] + n);
    }
    if (ok)
    {
        if (l == r)
            cout << "Yes\n";
        else
        {
            int mid = (l + r) >> 1;
            solve(ls, l, mid), solve(rs, mid + 1, r);
        }
    }
    while (stk.size() > s)
    {
        int x = stk.top().first, v = stk.top().second;
        hi[fa[x]] -= v, fa[x] = x;
        stk.pop();
    }
}

signed main()
{
    cin >> n >> m >> k;
    for (int i = 1, l, r; i <= m; i++)
    {
        cin >> u[i] >> v[i] >> l >> r;
        insert(1, 1, k, l + 1, r, i);
    }
    iota(fa + 1, fa + n + n + 1, 1);
    solve(1, 1, k);
    return 0;
}