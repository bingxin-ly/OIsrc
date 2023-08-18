#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 5, MOD = 1e9 + 7;
int n, m;
vector<int> g[N], h[N];

int tim, dfn[N], low[N], top, stk[N], cnt, col[N], siz[N];
void build(int u, int bin = 0)
{
    cnt += 1;
    while (bin != u)
        col[bin = stk[top--]] = cnt, siz[cnt] += 1;
}
void tarjan(int u, int bin)
{
    dfn[u] = low[u] = ++tim, stk[++top] = u;
    for (int v : g[u])
    {
        if (v == bin)
            continue;
        if (!dfn[v])
        {
            tarjan(v, u), low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                build(v);
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
}

long long ans, f[N][2], sbt[N], bin[N << 1];
void dp(int u, int p)
{
    sbt[u] = 1, f[u][0] = 1, f[u][1] = bin[siz[u]] - 1;
    for (int v : h[u])
    {
        if (v == p)
            continue;
        dp(v, u);
        sbt[u] += sbt[v];
        long long f0 = f[u][0] * f[v][0] * 2 % MOD;
        long long f1 = (f[u][1] * f[v][0] * 2 % MOD +
                   f[u][1] * f[v][1] % MOD +
                   f[u][0] * f[v][1] % MOD) %
                  MOD;
        f[u][0] = f0, f[u][1] = f1;
    }
    (ans += f[u][1] * bin[m - sbt[u] + (u == 1)] % MOD) %= MOD;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    tarjan(1, 0), build(1);
    for (int u = 1; u <= n; u++)
        for (int v : g[u])
            if (col[u] != col[v])
                h[col[u]].emplace_back(col[v]);
    bin[0] = 1;
    for (int i = 1; i <= m; i++)
        bin[i] = (bin[i - 1] << 1) % MOD;
    dp(1, 0);
    cout << ans;
    return 0;
}