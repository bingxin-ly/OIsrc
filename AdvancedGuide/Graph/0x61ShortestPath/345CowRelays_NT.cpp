#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int n, t, s, e, u[N], v[N], w[N], f[2][N];
vector<int> ps;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> t >> s >> e, ps.emplace_back(s), ps.emplace_back(e);
    for (int i = 1; i <= t; i++)
        cin >> w[i] >> u[i] >> v[i],
            ps.emplace_back(u[i]), ps.emplace_back(v[i]);
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    s = lower_bound(ps.begin(), ps.end(), s) - ps.begin() + 1;
    e = lower_bound(ps.begin(), ps.end(), e) - ps.begin() + 1;
    for (int i = 1; i <= t; i++)
        u[i] = lower_bound(ps.begin(), ps.end(), u[i]) - ps.begin() + 1,
        v[i] = lower_bound(ps.begin(), ps.end(), v[i]) - ps.begin() + 1;

    memset(f, 0x3f, sizeof(f)), f[0][s] = 0;
    for (int i = 1; i <= n; i++)
    {
        memset(f[i & 1], 0x3f, sizeof(f[i & 1]));
        for (int j = 1; j <= t; j++)
            f[i & 1][v[j]] = min(f[i & 1][v[j]], f[(i - 1) & 1][u[j]] + w[j]),
                  f[i & 1][u[j]] = min(f[i & 1][u[j]], f[(i - 1) & 1][v[j]] + w[j]);
    }
    cout << f[n & 1][e];
    return 0;
}