#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    static long long val[N << 2];
    function<void(int, int, int, long long *)> build;
    function<void(int, int, int, int, long long)> update;
    function<long long(int, int, int, int, int)> query;
    {
#define ls (p << 1)
#define rs (p << 1 | 1)
        memset(val, 0x3f, sizeof(val));
        function<void(int)> pushup = [&](int p)
        { val[p] = min(val[ls], val[rs]); };
        build = [&](int p, int l, int r, long long *arr)
        {
            if (l == r)
                return val[p] = arr[l], void();
            int m = (l + r) >> 1;
            build(ls, l, m, arr), build(rs, m + 1, r, arr);
            pushup(p);
        };
        update = [&](int p, int l, int r, int x, long long v)
        {
            if (l == r)
                return val[p] = v, void();
            int m = (l + r) >> 1;
            if (x <= m)
                update(ls, l, m, x, v);
            else
                update(rs, m + 1, r, x, v);
            pushup(p);
        };
        query = [&](int p, int l, int r, int ql, int qr)
        {
            if (ql <= l && r <= qr)
                return val[p];
            int m = (l + r) >> 1;
            long long ret = 1ll << 62;
            if (ql <= m)
                ret = min(ret, query(ls, l, m, ql, qr));
            if (qr > m)
                ret = min(ret, query(rs, m + 1, r, ql, qr));
            return ret;
        };
#undef ls
#undef rs
    }
    struct C
    {
        int l, r, w;
    } static cow[N];
    int n, l, r;
    {
        cin >> n >> l >> r;
        for (int i = 1; i <= n; i++)
            cin >> cow[i].l >> cow[i].r >> cow[i].w;
        sort(cow + 1, cow + n + 1, [](const C &x, const C &y)
             { return x.r < y.r || (x.r == y.r && x.l < y.l); });
    }
    static long long f[N];
    {
        memset(f, 0x3f, sizeof(f));
        f[l - 1] = 0, update(1, l - 1, r, l - 1, 0);
        for (int i = 1; i <= n; i++)
            f[cow[i].r] = min(f[cow[i].r], query(1, l - 1, r, cow[i].l - 1, cow[i].r - 1) + cow[i].w),
            update(1, l - 1, r, cow[i].r, f[cow[i].r]);
    }
    cout << (f[r] <= 5e9 ? f[r] : -1);
    return 0;
}