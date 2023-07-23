#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int n, t, s, e, p, u[N], v[N], w[N];
int dis[N][N], ans[N][N];
vector<int> ps;

void mul(int a[N][N], int b[N][N])
{
    static int c[N][N];
    memset(c, 0x3f, sizeof(c));
    for (int i = 1; i <= p; i++)
        for (int j = 1; j <= p; j++)
            for (int k = 1; k <= p; k++)
                c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
    memcpy(a, c, sizeof(c));
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> t >> s >> e, ps.emplace_back(s), ps.emplace_back(e);
    for (int i = 1; i <= t; i++)
        cin >> w[i] >> u[i] >> v[i],
            ps.emplace_back(u[i]), ps.emplace_back(v[i]);
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    p = ps.size();
    s = lower_bound(ps.begin(), ps.end(), s) - ps.begin() + 1;
    e = lower_bound(ps.begin(), ps.end(), e) - ps.begin() + 1;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= t; i++)
    {
        u[i] = lower_bound(ps.begin(), ps.end(), u[i]) - ps.begin() + 1;
        v[i] = lower_bound(ps.begin(), ps.end(), v[i]) - ps.begin() + 1;
        dis[u[i]][v[i]] = dis[v[i]][u[i]] = min(dis[u[i]][v[i]], w[i]);
    }

    memset(ans, 0x3f, sizeof(ans)), ans[s][s] = 0;
    // 广义矩阵快速幂
    for (; n; n >>= 1)
    {
        if (n & 1)
            mul(ans, dis);
        mul(dis, dis);
    }
    cout << ans[s][e];
    return 0;
}