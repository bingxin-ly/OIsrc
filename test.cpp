#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 50003;
struct Query
{
    int l, r, id, opt;
    LL c;
} q[N], q1[N], q2[N];
int n, m;
LL seg[N << 2], tag[N << 2];
LL ans[N];
inline void pushup(int x) { seg[x] = seg[x << 1] + seg[x << 1 | 1]; }
inline void pushdown(int x, int L, int R)
{
    int mid = L + R >> 1;
    seg[x << 1] += tag[x] * (mid - L + 1);
    seg[x << 1 | 1] += tag[x] * (R - mid);
    tag[x << 1] += tag[x];
    tag[x << 1 | 1] += tag[x];
    tag[x] = 0;
}
inline void change(int x, int L, int R, int l, int r, int v)
{
    if (l <= L && R <= r)
    {
        seg[x] += (R - L + 1) * v;
        tag[x] += v;
        return;
    }
    int mid = L + R >> 1;
    pushdown(x, L, R);
    if (l <= mid)
        change(x << 1, L, mid, l, r, v);
    if (mid < r)
        change(x << 1 | 1, mid + 1, R, l, r, v);
    pushup(x);
}
inline LL query(int x, int L, int R, int l, int r)
{
    if (l <= L && R <= r)
        return seg[x];
    int mid = L + R >> 1;
    LL ans = 0;
    pushdown(x, L, R);
    if (l <= mid)
        ans += query(x << 1, L, mid, l, r);
    if (mid < r)
        ans += query(x << 1 | 1, mid + 1, R, l, r);
    return ans;
}
LL cur[N];
inline void solve(int ql, int qr, LL l, LL r)
{
    if (ql > qr || l > r)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++)
            if (q[i].opt == 2)
                ans[q[i].id] = l;
        return;
    }
    LL mid = l + r >> 1;
    for (int i = ql; i <= qr; i++)
        if (q[i].opt == 1 && q[i].c > mid)
            change(1, 1, n, q[i].l, q[i].r, 1);
        else if (q[i].opt == 2)
            cur[i] = query(1, 1, n, q[i].l, q[i].r);
    for (int i = ql; i <= qr; i++)
        if (q[i].opt == 1 && q[i].c > mid)
            change(1, 1, n, q[i].l, q[i].r, -1);
    int cnt1 = 0, cnt2 = 0;
    for (int i = ql; i <= qr; i++)
        if (q[i].opt == 2)
        {
            if (cur[i] >= q[i].c)
                q2[cnt2++] = q[i];
            else
            {
                q[i].c -= cur[i];
                q1[cnt1++] = q[i];
            }
        }
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
    solve(ql, ql + cnt1 - 1, l, mid);
    solve(ql + cnt1, qr, mid + 1, r);
}
int main()
{
    cin >> n >> m;
    int tot = 0;
    for (int i = 1; i <= m; i++)
    {
        cin >> q[i].opt >> q[i].l >> q[i].r >> q[i].c;
        if (q[i].opt == 2)
            q[i].id = tot++;
    }
    solve(1, m, 0, n);
    for (int i = 0; i < tot; i++)
        printf("%lld\n", ans[i]);
}
