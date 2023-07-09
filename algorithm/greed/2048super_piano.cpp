#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

constexpr int N = 5e5 + 5, LOG = 20;
long long sum[N];
namespace ST
{
    int st[N][LOG];
    void pretask(int n)
    {
        for (int i = 1; i <= n; i++)
            st[i][0] = i;
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                int x = st[i][j - 1], y = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = sum[x] > sum[y] ? x : y;
            }
    }
    int query(int l, int r)
    {
        int k = log2(r - l + 1),
            x = st[l][k], y = st[r - (1 << k) + 1][k];
        return sum[x] > sum[y] ? x : y;
    }
}
struct seg
{
    int o, l, r, p;
    seg(int o_, int l_, int r_) : o(o_), l(l_), r(r_), p(ST::query(l_, r_)) {}
    bool operator<(const seg &t) const
    {
        return sum[p] - sum[o - 1] < sum[t.p] - sum[t.o - 1];
    }
};
priority_queue<seg> q;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, k, L, R;
    cin >> n >> k >> L >> R;
    for (int i = 1; i <= n; i++)
        cin >> sum[i], sum[i] += sum[i - 1];
    ST::pretask(n);
    for (int i = 1; i <= n; i++)
        if (i + L - 1 <= n)
            q.emplace(i, i + L - 1, min(i + R - 1, n));
    long long ans = 0;
    while (k--)
    {
        auto [o, l, r, p] = q.top();
        q.pop();
        ans += sum[p] - sum[o - 1];
        if (l != p)
            q.emplace(o, l, p - 1);
        if (p != r)
            q.emplace(o, p + 1, r);
    }
    cout << ans;
    return 0;
}