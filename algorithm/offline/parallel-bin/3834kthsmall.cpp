#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, INF = 1e9;
int n, m, ans[N];
struct BIT
{
    int val[N];
    static inline int lowbit(int x) { return x & -x; }
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

struct Query
{
    int l, r, k, id, type;
} q[N * 2], q1[N * 2], q2[N * 2];

void solve(int l, int r, int ql, int qr)
{
    if (ql > qr)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++)
            if (q[i].type == 2)
                ans[q[i].id] = l;
        return;
    }
    int mid = (l + r) / 2, cnt1 = 0, cnt2 = 0;
    for (int i = ql; i <= qr; i++)
        if (q[i].type == 1)
        {
            if (q[i].l <= mid)
                tr.add(q[i].id, 1), q1[++cnt1] = q[i];
            else
                q2[++cnt2] = q[i];
        }
        else
        {
            int x = tr.presum(q[i].r) - tr.presum(q[i].l - 1);
            if (q[i].k <= x)
                q1[++cnt1] = q[i];
            else
                q[i].k -= x, q2[++cnt2] = q[i];
        }
    // rollback changes
    for (int i = 1; i <= cnt1; i++)
        if (q1[i].type == 1)
            tr.add(q1[i].id, -1);
    for (int i = 1; i <= cnt1; i++)
        q[i + ql - 1] = q1[i];
    for (int i = 1; i <= cnt2; i++)
        q[i + cnt1 + ql - 1] = q2[i];
    solve(l, mid, ql, cnt1 + ql - 1);
    solve(mid + 1, r, cnt1 + ql, qr);
}

pair<int, int> b[N];
int a[N], raw[N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> b[i].first, b[i].second = i;

    sort(b + 1, b + n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (b[i].first != b[i - 1].first)
            cnt++;
        a[b[i].second] = cnt;
        raw[cnt] = b[i].first;
    }
    int tot = 0;
    for (int i = 1; i <= n; i++)
        q[++tot] = {a[i], -1, -1, i, 1};
    for (int i = 1; i <= m; i++)
    {
        int l, r, k;
        cin >> l >> r >> k;
        q[++tot] = {l, r, k, i, 2};
    }
    solve(0, cnt + 1, 1, tot);
    for (int i = 1; i <= m; i++)
        cout << raw[ans[i]] << endl;
    return 0;
}