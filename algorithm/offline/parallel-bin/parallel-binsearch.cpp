// 易于理解的朴素版本
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
struct num
{
    int p, x;
}; // 位于数列中第 p 项的数的值为 x

struct query
{
    int id, l, r, k;
}; // 一个编号为 id, 询问 [l,r] 中第 k 小数的询问

int n, m, ans[N];

struct BIT
{
    int t[N];
    static inline int lowbit(int x) { return x & -x; }
    inline void add(int p, int x) // 树状数组, 在 p 位置加上 x
    {
        for (; p <= n; p += lowbit(p))
            t[p] += x;
    }
    inline int presum(int p) // 树状数组, 求 [1,p] 的和
    {
        int res = 0;
        for (; p; p -= lowbit(p))
            res += t[p];
        return res;
    }
} tr;

void solve(int l, int r, const vector<num> &a, vector<query> q) // a中为给定数列中值在值域区间 [l,r] 中的数
{
    int mid = (l + r) / 2;
    if (l == r)
    {
        for (const auto &i : q)
            ans[i.id] = l;
        return;
    }
    vector<num> a1, a2;
    for (const auto &i : a)
        if (i.x <= mid)
            a1.push_back(i), tr.add(i.p, 1);
        else
            a2.push_back(i);
    vector<query> q1, q2;
    for (auto &i : q)
    {
        int t = tr.presum(i.r) - tr.presum(i.l - 1);
        if (i.k <= t)
            q1.push_back(i);
        else
            i.k -= t, q2.push_back(i);
    }

    // rollback changes
    for (const auto &i : a1)
        tr.add(i.p, -1);
    if (!a1.empty())
        solve(l, mid, a1, q1);
    if (!a2.empty())
        solve(mid + 1, r, a2, q2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    vector<num> a(n);
    for (int i = 0; i < n; i++)
        a[i].p = i + 1, cin >> a[i].x;

    vector<query> q(m);
    for (int i = 0; i < m; i++)
    {
        int l, r, k;
        cin >> l >> r >> k;
        q[i] = {i + 1, l, r, k};
    }

    solve(0, 1e9, a, q);

    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
    return 0;
}
