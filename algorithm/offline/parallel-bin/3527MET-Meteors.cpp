#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 6e5 + 10;
int n, m, ans[N];
struct tree_array
{
    int v[N];
    static inline int lowbit(int x) { return x & -x; }
    void add(int p, int x)
    {
        for (; p <= 2 * m; p += lowbit(p))
            v[p] += x;
    }
    int presum(int p)
    {
        int res = 0;
        for (; p; p -= lowbit(p))
            res += v[p];
        return res;
    }
} bit;

vector<int> station[N];
struct query
{
    int id, k;
} q[N], lq[N], rq[N];
struct modify
{
    int l, r, val;
} mo[N];

void solve(int l, int r, int st, int ed)
{
    if (st > ed)
        return;
    if (l == r)
    {
        for (int i = st; i <= ed; i++)
            ans[q[i].id] = l;
        return;
    }

    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = l; i <= mid; i++)
        bit.add(mo[i].l, mo[i].val), bit.add(mo[i].r + 1, -mo[i].val);

    for (int i = st; i <= ed; i++)
    {
        int cnt = 0;
        for (auto j : station[q[i].id])
        {
            cnt += bit.presum(j) + bit.presum(j + m);
            if (cnt > q[i].k)
                break;
        }
        if (q[i].k <= cnt)
            lq[++cnt1] = q[i];
        else
            q[i].k -= cnt, rq[++cnt2] = q[i];
    }

    for (int i = l; i <= mid; i++)
        bit.add(mo[i].l, -mo[i].val), bit.add(mo[i].r + 1, mo[i].val);

    for (int i = 1; i <= cnt1; i++)
        q[st + i - 1] = lq[i];
    for (int i = 1; i <= cnt2; i++)
        q[st + cnt1 + i - 1] = rq[i];

    solve(l, mid, st, st + cnt1 - 1), solve(mid + 1, r, st + cnt1, ed);
}

signed main()
{
    cin >> n >> m;
    for (int i = 1, x; i <= m; i++)
        cin >> x, station[x].emplace_back(i);

    for (int i = 1; i <= n; i++)
    {
        q[i].id = i;
        cin >> q[i].k;
    }

    int k;
    cin >> k;
    for (int i = 1; i <= k; i++)
    {
        int l, r, val;
        cin >> l >> r >> val;
        if (r < l)
            r += m;
        mo[i] = {l, r, val};
    }

    solve(1, k + 1, 1, n);

    for (int i = 1; i <= n; i++)
        if (ans[i] == k + 1)
            puts("NIE");
        else
            cout << ans[i] << '\n';
    return 0;
}