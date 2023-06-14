#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 10;
int sum[N << 2], mxn[N << 2], sem[N << 2], num[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p)
{
    sum[p] = sum[ls] + sum[rs];
    mxn[p] = max(mxn[ls], mxn[rs]);
    if (mxn[ls] == mxn[rs])
        sem[p] = max(sem[ls], sem[rs]),
        num[p] = num[ls] + num[rs];
    else
        sem[p] = max(sem[ls], sem[rs]),
        sem[p] = max(sem[p], min(mxn[ls], mxn[rs])),
        num[p] = mxn[ls] > mxn[rs] ? num[ls] : num[rs];
}
void build(int p, int l, int r)
{
    if (l == r)
    {
        cin >> sum[p], mxn[p] = sum[p], sem[p] = -1, num[p] = 1;
        return;
    }

    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p);
}
void spread(int p, int x)
{
    if (x >= mxn[p])
        return;
    sum[p] -= num[p] * (mxn[p] - x);
    mxn[p] = x;
}
void pushdown(int p) { spread(ls, mxn[p]), spread(rs, mxn[p]); }
void update(int p, int l, int r, int ql, int qr, int x)
{
    if (mxn[p] <= x)
        return;
    if (ql <= l && r <= qr && sem[p] < x)
        return spread(p, x);

    pushdown(p);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(ls, l, mid, ql, qr, x);
    if (qr > mid)
        update(rs, mid + 1, r, ql, qr, x);
    pushup(p);
}

int qmax(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return mxn[p];

    pushdown(p);
    int mid = (l + r) >> 1, lt = 0, rt = 0;
    if (ql <= mid)
        lt = qmax(ls, l, mid, ql, qr);
    if (qr > mid)
        rt = qmax(rs, mid + 1, r, ql, qr);
    return max(lt, rt);
}
int qsum(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return sum[p];

    pushdown(p);
    int mid = (l + r) >> 1, res = 0;
    if (ql <= mid)
        res += qsum(ls, l, mid, ql, qr);
    if (qr > mid)
        res += qsum(rs, mid + 1, r, ql, qr);
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;
        build(1, 1, n);
        while (m--)
        {
            int q, l, r, x;
            cin >> q >> l >> r;
            if (q == 0)
                cin >> x, update(1, 1, n, l, r, x);
            else if (q == 1)
                cout << qmax(1, 1, n, l, r) << '\n';
            else
                cout << qsum(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}