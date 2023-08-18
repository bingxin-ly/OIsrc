#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 5;
int arr[N], rev[N << 2];
struct info
{
    long long sum, pre, suf, mxn;
    int prep, sufp, mxnl, mxnr;
} I{0, 0, 0, 0, -1, -1, -1, -1}, pos[N << 2], neg[N << 2];
info operator+(const info &x, const info &y)
{
    info z = I;
    z.sum = x.sum + y.sum;
    if (x.pre > z.pre)
        z.pre = x.pre, z.prep = x.prep;
    if (x.sum + y.pre > z.pre)
        z.pre = x.sum + y.pre, z.prep = y.prep;

    if (y.suf > z.suf)
        z.suf = y.suf, z.sufp = y.sufp;
    if (x.suf + y.sum > z.suf)
        z.suf = x.suf + y.sum, z.sufp = x.sufp;

    if (x.mxn > z.mxn)
        z.mxn = x.mxn, z.mxnl = x.mxnl, z.mxnr = x.mxnr;
    if (y.mxn > z.mxn)
        z.mxn = y.mxn, z.mxnl = y.mxnl, z.mxnr = y.mxnr;
    if (x.suf + y.pre > z.mxn)
        z.mxn = x.suf + y.pre, z.mxnl = x.sufp, z.mxnr = y.prep;
    return z;
}

#define ls (p << 1)
#define rs (p << 1 | 1)
void init(int p, int o)
{
    int pv = max(0, arr[o]), pp = arr[o] < 0 ? -1 : o;
    pos[p] = {arr[o], pv, pv, pv, pp, pp, pp, pp};
    int nv = max(0, -arr[o]), np = arr[o] > 0 ? -1 : o;
    neg[p] = {-arr[o], nv, nv, nv, np, np, np, np};
}
void pushup(int p) { pos[p] = pos[ls] + pos[rs], neg[p] = neg[ls] + neg[rs]; }
void swp(int p) { rev[p] ^= 1, swap(pos[p], neg[p]); }
void pushdown(int p) { rev[p] && (swp(ls), swp(rs), rev[p] = 0); }

void build(int p, int l, int r)
{
    if (l == r)
        return init(p, l);
    int m = (l + r) >> 1;
    build(ls, l, m), build(rs, m + 1, r), pushup(p);
}
void update(int p, int l, int r, int x)
{
    if (l == r)
        return init(p, x);
    int m = (l + r) >> 1;
    if (x <= m)
        update(ls, l, m, x);
    else
        update(rs, m + 1, r, x);
    pushup(p);
}
void flip(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return swp(p);
    pushdown(p);
    int m = (l + r) >> 1;
    if (ql <= m)
        flip(ls, l, m, ql, qr);
    if (qr > m)
        flip(rs, m + 1, r, ql, qr);
    pushup(p);
}
info query(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return pos[p];
    pushdown(p);
    int m = (l + r) >> 1;
    info ret = I;
    if (ql <= m)
        ret = query(ls, l, m, ql, qr);
    if (qr > m)
        ret = ret + query(rs, m + 1, r, ql, qr);
    return ret;
}
signed Luogu()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    build(1, 1, n);
    long long ans = 0;
    vector<pair<int, int>> ope;
    while (k--)
    {
        info res = pos[1];
        if (res.mxnl == -1)
            break;
        ans += res.mxn, ope.emplace_back(res.mxnl, res.mxnr);
        flip(1, 1, n, res.mxnl, res.mxnr);
    }
    cout << ans << '\n';
    return 0;
}
signed CodeForces()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    build(1, 1, n);
    cin >> m;
    for (int op, l, r, k; m--;)
    {
        cin >> op;
        if (!op)
            cin >> l >> arr[l], update(1, 1, n, l);
        else
        {
            cin >> l >> r >> k;
            int ans = 0;
            vector<pair<int, int>> ope;
            while (k--)
            {
                info res = query(1, 1, n, l, r);
                if (res.mxnl == -1)
                    break;
                ans += res.mxn, ope.emplace_back(res.mxnl, res.mxnr);
                flip(1, 1, n, res.mxnl, res.mxnr);
            }
            cout << ans << '\n';
            for (auto pr : ope)
                flip(1, 1, n, pr.first, pr.second);
        }
    }
    return 0;
}