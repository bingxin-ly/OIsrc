#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e2 + 10, Q = 6e4 + 10;
int n, ans[Q];
namespace BIT
{
    int v[N][N];
    inline int lowbit(int x) { return x & -x; }

    void add(int x, int y, int val)
    {
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= n; j += lowbit(j))
                v[i][j] += val;
    }
    int presum(int x, int y)
    {
        if (!x || !y)
            return 0;
        int res = 0;
        for (int i = x; i; i -= lowbit(i))
            for (int j = y; j; j -= lowbit(j))
                res += v[i][j];
        return res;
    }
    int ask(int x1, int y1, int x2, int y2)
    {
        return presum(x2, y2) - presum(x1 - 1, y2) - presum(x2, y1 - 1) + presum(x1 - 1, y1 - 1);
    }
}

const int S = N * N + Q;
struct query
{
    int id, x1, y1, x2, y2, k;
} q[S], q1[S], q2[S];

void solve(int l, int r, int ql, int qr)
{
    if (ql > qr)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++)
            if (q[i].id)
                ans[q[i].id] = l;
        return;
    }

    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = ql; i <= qr; i++)
        if (!q[i].id)
            if (q[i].k <= mid)
                BIT::add(q[i].x1, q[i].y1, 1), q1[++cnt1] = q[i];
            else
                q2[++cnt2] = q[i];
        else
        {
            int s = BIT::ask(q[i].x1, q[i].y1, q[i].x2, q[i].y2);
            if (q[i].k <= s)
                q1[++cnt1] = q[i];
            else
                q[i].k -= s, q2[++cnt2] = q[i];
        }

    // rollback
    for (int i = 1; i <= cnt1; i++)
        if (!q1[i].id)
            BIT::add(q1[i].x1, q1[i].y1, -1);
    for (int i = 1; i <= cnt1; i++)
        q[ql + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; i++)
        q[ql + cnt1 + i - 1] = q2[i];

    solve(l, mid, ql, ql + cnt1 - 1), solve(mid + 1, r, ql + cnt1, qr);
}

signed main()
{
    ios::sync_with_stdio(false);
    int m;
    cin >> n >> m;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int v;
            cin >> v;
            q[++cnt] = {0, i, j, 0, 0, v};
        }

    for (int i = 1; i <= m; i++)
    {
        int x1, y1, x2, y2, k;
        cin >> x1 >> y1 >> x2 >> y2 >> k;
        q[++cnt] = {i, x1, y1, x2, y2, k};
    }

    solve(0, 1e9, 1, cnt);

    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
    return 0;
}