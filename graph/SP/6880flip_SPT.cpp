#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205, M = 5e4 + 5;
int n, m, u[M], v[M], w[M], vis[M],
    f[N][N], g[N][N], frm[N], hvis[N];

long long d[M], ans;
long long fdis[N], gdis[N], hdis[N];
void solve(int s, int t)
{
    memset(fdis, 0x3f, sizeof(fdis)), fdis[s] = 0;
    memset(gdis, 0x3f, sizeof(gdis)), gdis[t] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
            {
                if (f[j][k] && fdis[k] > fdis[j] + w[f[j][k]])
                    fdis[k] = fdis[j] + w[f[j][k]], frm[k] = f[j][k];
                if (f[j][k] && gdis[j] > gdis[k] + w[f[j][k]])
                    gdis[j] = gdis[k] + w[f[j][k]];
            }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++)
        vis[frm[i]] = 1;
    for (int i = 1; i <= m; i++)
    {
        if (!vis[i])
            d[i] += min(fdis[t], fdis[v[i]] + w[i] + gdis[u[i]]);
        else
        {
            memset(hvis, 0, sizeof(hvis));
            memset(hdis, 0x3f, sizeof(hdis)), hdis[s] = 0;
            for (int _ = 1; _ <= n; _++)
            {
                int c = 0;
                for (int j = 1; j <= n; j++)
                    if (!hvis[j] && hdis[j] < hdis[c])
                        c = j;
                hvis[c] = 1;
                for (int j = 1; j <= n; j++)
                {
                    int edg = c == u[i] && j == v[i] ? g[c][j] : f[c][j];
                    if (edg)
                        hdis[j] = min(hdis[j], hdis[c] + w[edg]);
                }
                if (c == v[i])
                    hdis[u[i]] = min(hdis[u[i]], hdis[c] + w[i]);
            }
            d[i] += hdis[t];
        }
    }
    ans += fdis[t];
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m, w[0] = 1 << 30;
    for (int i = 1; i <= m; i++)
    {
        cin >> u[i] >> v[i] >> w[i] >> d[i];
        if (w[i] < w[f[u[i]][v[i]]])
            g[u[i]][v[i]] = f[u[i]][v[i]], f[u[i]][v[i]] = i;
        else if (w[i] < w[g[u[i]][v[i]]])
            g[u[i]][v[i]] = i;
    }
    solve(1, n), solve(n, 1);
    for (int i = 1; i <= m; i++)
        ans = min(ans, d[i]);
    cout << (ans > 2e9 ? -1 : ans);
    return 0;
}