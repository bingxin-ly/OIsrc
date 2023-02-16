#include <bits/stdc++.h>
using namespace std;

const int MAX = 3e2 + 10;
int n, m, f[MAX][MAX];
int cnt, head[MAX], siz[MAX], val[MAX];

struct edge
{
    int pre, to;
} edges[MAX];
// vector<edge> courses[MAX];

void add(int u, int v)
{
    edges[++cnt].pre = head[u];
    edges[cnt].to = v;
    head[u] = cnt;
}
void dp(int u)
{
    for (int i = head[u]; i; i = edges[i].pre)
    {
        int s = edges[i].to;
        dp(s);
        for (int j = m + 1; j > 0; j--)
            for (int k = 0; k < j; k++)
                f[u][j] = max(f[u][j], f[s][k] + f[u][j - k]);
    }
}
void dp_optimized(int u)
{
    siz[u]++;
    for (int i = head[u]; i; i = edges[i].pre)
    {
        int s = edges[i].to;
        dp_optimized(s);
        for (int j = min(m + 1, siz[u]); j > 0; j--)
            for (int k = 0; k < min(siz[s], j); k++)
                // for (int k = 1; k <= min(siz[s], j); k++)
                f[u][j] = max(f[u][j], f[s][k] + f[u][j - k]);
        siz[u] += siz[s];
    }
}
void dfs(int u, int t)
{
    if (t <= 0)
        return;
    for (int i = head[u]; i; i = edges[i].pre)
    {
        int v = edges[i].to;
        for (int k = 0; k < t; ++k)
            f[v][k] = f[u][k] + val[v];
        dfs(v, t - 1);
        for (int k = 1; k <= t; ++k)
            f[u][k] = max(f[u][k], f[v][k - 1]);
    }
}
void solve(int u)
{
    for (int i = head[u]; i; i = edges[i].pre)
        solve(edges[i].to);

    // 背包
    for (int i = head[u]; i; i = edges[i].pre)
        for (int j = m, s = edges[i].to; j > 0; j--)
            for (int k = 0; k < j; ++k)
                f[u][j] = max(f[u][j], f[u][j - k] + f[s][k]);
}

int main()
{
    cin >> n >> m;
    int pre, credit;
    for (int i = 1; i <= n; i++)
    {
        cin >> pre >> credit;
        val[i] = credit;
        add(pre, i);
    }
    // dp(0);
    // dp_optimized(0);
    dfs(0, m);
    cout << f[0][m] << endl;
    /* m++;
    solve(0);
    cout << f[0][m] << endl; */
    return 0;
}
