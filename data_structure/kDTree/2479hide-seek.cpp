#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
struct point
{
    int ls, rs;
    int val[2], mxv[2], mnv[2];
    /* 我们可以维护一个子树中的所有结点在每一维上的坐标的最小值和最大值。
    这样就维护出了这个超长方体，查询时可剪枝 */
    int &operator[](int x) { return val[x]; }
} t[N], p[N];
void pushup(int p)
{
    int ls = t[p].ls, rs = t[p].rs;
    for (int i = 0; i <= 1; i++)
    {
        t[p].mnv[i] = t[p].mxv[i] = t[p][i];
        if (ls)
            t[p].mnv[i] = min(t[p].mnv[i], t[ls].mnv[i]),
            t[p].mxv[i] = max(t[p].mxv[i], t[ls].mxv[i]);
        if (rs)
            t[p].mnv[i] = min(t[p].mnv[i], t[rs].mnv[i]),
            t[p].mxv[i] = max(t[p].mxv[i], t[rs].mxv[i]);
    }
}
point pos;
int ans;
int build(int l, int r, int d)
{
    int m = (l + r) >> 1;
    nth_element(p + l, p + m, p + r + 1, [d](point &a, point &b)
                { return a[d] < b[d]; }),
        t[m] = p[m];
    for (int i = 0; i <= 1; i++)
        t[m].mnv[i] = t[m].mxv[i] = t[m][i];
    if (l < m)
        t[m].ls = build(l, m - 1, d ^ 1);
    if (r > m)
        t[m].rs = build(m + 1, r, d ^ 1);
    pushup(m);
    return m;
}
int calc(point &a, point &b)
{
    return abs(a[1] - b[1]) + abs(a[0] - b[0]);
}
void querymax(int p)
{
    static auto calcmax = [](const point &p)
    {
        int ans = 0;
        for (int i = 0; i <= 1; i++)
            ans += max(abs(pos[i] - p.mxv[i]), abs(pos[i] - p.mnv[i]));
        return ans;
    };
    ans = max(ans, calc(t[p], pos));
    int ls = t[p].ls, rs = t[p].rs, dl = INT_MIN, dr = INT_MIN;
    ls && (dl = calcmax(t[ls])), rs && (dr = calcmax(t[rs]));
    if (dl > dr)
    {
        dl > ans && (querymax(ls), true);
        dr > ans && (querymax(rs), true);
    }
    else
    {
        dr > ans && (querymax(rs), true);
        dl > ans && (querymax(ls), true);
    }
}
void querymin(int p)
{
    static auto calcmin = [](const point &p)
    {
        int ans = 0;
        for (int i = 0; i <= 1; i++)
            ans += max(pos[i] - p.mxv[i], 0) + max(p.mnv[i] - pos[i], 0);
        return ans;
    };
    int tmp = calc(pos, t[p]);
    tmp && (ans = min(ans, tmp));
    int ls = t[p].ls, rs = t[p].rs, dl = INT_MAX, dr = INT_MAX;
    ls && (dl = calcmin(t[ls])), rs && (dr = calcmin(t[rs]));
    if (dl < dr)
    {
        dl < ans && (querymin(ls), true);
        dr < ans && (querymin(rs), true);
    }
    else
    {
        dr < ans && (querymin(rs), true);
        dl < ans && (querymin(ls), true);
    }
}
int rt, x[N], y[N];
int query(bool tp, int x, int y)
{
    pos[0] = x, pos[1] = y;
    if (!tp)
        ans = INT_MAX, querymin(rt);
    else
        ans = INT_MIN, querymax(rt);
    return ans;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i],
            p[i][0] = x[i], p[i][1] = y[i];
    rt = build(1, n, 0);
    int res = INT_MAX;
    for (int i = 1; i <= n; i++)
    {
        int minv = query(false, x[i], y[i]), maxv = query(true, x[i], y[i]);
        res = min(res, maxv - minv);
    }
    cout << res;
    return 0;
}