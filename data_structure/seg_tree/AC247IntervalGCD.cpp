#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 10;
int n, src[N];

// treearray
namespace BIT
{
    int v[N];
    inline int lowbit(int x) { return x & -x; }
    void build()
    {
        for (int i = 1; i <= n; i++)
        {
            v[i] += src[i] - src[i - 1];
            (i + lowbit(i) <= n) &&
                (v[i + lowbit(i)] += v[i]);
        }
    }
    inline void add(int p, int x)
    {
        for (; p <= n; p += lowbit(p))
            v[p] += x;
    }
    inline int query(int p)
    {
        int res = 0;
        for (; p; p -= lowbit(p))
            res += v[p];
        return res;
    }
}

int gcd(int a, int b)
{
    if (!a || !b)
        return a ? abs(a) : abs(b);
    else
        return gcd(b, a % b);
}

// segment_tree
namespace SEGTR
{
    int tr[N << 2];
#define ls p << 1
#define rs p << 1 | 1
    inline void pushup(int p)
    {
        tr[p] = gcd(tr[ls], tr[rs]);
    }
    void build(int p, int l, int r)
    {
        if (l == r)
            return tr[p] = src[l] - src[l - 1], void();
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        pushup(p);
    }
    void add(int p, int l, int r, int pos, int v)
    {
        if (l == r)
            return tr[p] += v, void();

        int mid = (l + r) >> 1;
        if (pos <= mid)
            add(ls, l, mid, pos, v);
        else
            add(rs, mid + 1, r, pos, v);
        pushup(p);
    }
    int query(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return tr[p];

        int mid = (l + r) >> 1;
        int lt = 0, rt = 0;
        if (ql <= mid)
            lt = query(ls, l, mid, ql, qr);
        if (qr > mid)
            rt = query(rs, mid + 1, r, ql, qr);
        return gcd(lt, rt);
    }
}

inline void update(int l, int r, int d)
{
    BIT::add(l, d), BIT::add(r + 1, -d);
    SEGTR::add(1, 1, n, l, d);
    if (r + 1 <= n)
        SEGTR::add(1, 1, n, r + 1, -d);
}
inline int query(int l, int r)
{
    return gcd(BIT::query(l), SEGTR::query(1, 1, n, l + 1, r));
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> src[i];

    BIT::build(), SEGTR::build(1, 1, n);

    char opt;
    for (int l, r, d; m--;)
    {
        cin >> opt >> l >> r;
        if (opt == 'C')
            cin >> d, update(l, r, d);
        else
            cout << query(l, r) << '\n';
    }
    return 0;
}