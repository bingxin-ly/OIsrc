#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int n, cur[N], ans[N];
namespace BIT
{
    int diff[N], ex[N];
    inline int lowbit(int x) { return x & -x; }
    void add(int *tr, int p, int x)
    {
        for (; p <= n; p += lowbit(p))
            tr[p] += x;
    }
    int presum(const int *tr, int p)
    {
        int res = 0;
        for (; p; p -= lowbit(p))
            res += tr[p];
        return res;
    }
    void add(int l, int r, int x)
    {
        add(diff, l, x), add(diff, r + 1, -x);
        add(ex, l, x * (l - 1)), add(ex, r + 1, -x * r);
    }
    int presum(int l, int r)
    {
        return (r * presum(diff, r) - presum(ex, r)) -
               ((l - 1) * presum(diff, l - 1) - presum(ex, l - 1));
    }
}

struct option
{
    int id, l, r, c;
} q[N << 1], q1[N << 1], q2[N << 1];

void solve(int l, int r, int ql, int qr)
{
    if (ql > qr || l > r)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++)
            if (q[i].id)
                ans[q[i].id] = l;
        return;
    }

    int mid = (l + r) >> 1;
    for (int i = ql; i <= qr; i++)
        if (!q[i].id && q[i].c > mid)
            BIT::add(q[i].l, q[i].r, 1);
        else if (q[i].id)
            cur[i] = BIT::presum(q[i].l, q[i].r);

    for (int i = ql; i <= qr; i++)
        if (!q[i].id && q[i].c > mid)
            BIT::add(q[i].l, q[i].r, -1);

    int cnt1 = 0, cnt2 = 0;
    for (int i = ql; i <= qr; i++)
        if (q[i].id)
            if (cur[i] >= q[i].c)
                q2[cnt2++] = q[i];
            else
                q[i].c -= cur[i], q1[cnt1++] = q[i];
        else
        {
            if (q[i].c <= mid)
                q1[cnt1++] = q[i];
            else
                q2[cnt2++] = q[i];
        }

    for (int i = 0; i < cnt1; i++)
        q[ql + i] = q1[i];
    for (int i = 0; i < cnt2; i++)
        q[ql + cnt1 + i] = q2[i];

    solve(l, mid, ql, ql + cnt1 - 1), solve(mid + 1, r, ql + cnt1, qr);
}

signed main()
{
    ios::sync_with_stdio(false);
    int m, id = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int opt, l, r, c;
        cin >> opt >> l >> r >> c;
        if (opt == 1)
            q[i] = {0, l, r, c};
        else
            q[i] = {++id, l, r, c};
    }
    solve(0, n, 1, m);
    for (int i = 1; i <= id; i++)
        cout << ans[i] << '\n';
    return 0;
}