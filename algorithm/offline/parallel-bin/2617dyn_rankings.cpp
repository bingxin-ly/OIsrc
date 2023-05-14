#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
struct option
{
    int id, l, r, k;
} q[N], q1[N], q2[N];

int n, a[N], ans[N];
struct tree_array
{
    int val[N];
    inline int lowbit(int x) { return x & -x; }
    void add(int p, int x)
    {
        for (; p <= n; p += lowbit(p))
            val[p] += x;
    }
    int presum(int p)
    {
        int ans = 0;
        for (; p; p -= lowbit(p))
            ans += val[p];
        return ans;
    }
} tr;

// 当前二分的值域范围为 [l, r]，处理的下标区间为 [L, R]
void solve(int l, int r, int ql, int qr)
{
    if (l > r || ql > qr)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++)
            if (q[i].id)
                ans[q[i].id] = l;
        return;
    }
    int cnt1 = 0, cnt2 = 0,
        mid = (l + r) >> 1;
    for (int i = ql; i <= qr; i++)
        if (q[i].id)
        {
            int t = tr.presum(q[i].r) - tr.presum(q[i].l - 1);
            if (q[i].k <= t)
                q1[++cnt1] = q[i];
            else
                q[i].k -= t, q2[++cnt2] = q[i];
        }
        else
        {
            if (q[i].r <= mid)
                tr.add(q[i].l, q[i].k), q1[++cnt1] = q[i];
            else
                q2[++cnt2] = q[i];
        }
    for (int i = 1; i <= cnt1; i++)
        if (!q1[i].id)
            tr.add(q1[i].l, -q1[i].k);

    for (int i = 1; i <= cnt1; i++)
        q[ql + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; i++)
        q[ql + cnt1 + i - 1] = q2[i];
    solve(l, mid, ql, ql + cnt1 - 1), solve(mid + 1, r, ql + cnt1, qr);
}

int main()
{
    int m, cnt = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i], q[++cnt] = {0, i, a[i], 1};
    int id = 0;
    while (m--)
    {
        char opt;
        int l, r, k;
        cin >> opt >> l >> r;
        if (opt == 'Q')
            cin >> k, q[++cnt] = {++id, l, r, k};
        else
        {
            q[++cnt] = {0, l, a[l], -1};
            q[++cnt] = {0, l, r, 1};
            a[l] = r;
        }
    }
    solve(0, 1e9, 1, cnt);
    for (int i = 1; i <= id; i++)
        cout << ans[i] << '\n';
    return 0;
}