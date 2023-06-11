#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

const int N = 1e4 + 10;
int idx, head[N], edge[N << 1], val[N << 1], nxt[N << 1];
inline void contact(int u, int v, int w)
{
    nxt[++idx] = head[u], head[u] = idx,
    edge[idx] = v, val[idx] = w;
}

int n, m, rt, sum, query[110], ans[110];
int vis[N], siz[N], dp[N];
void root(int u, int p)
{
    dp[u] = 0, siz[u] = 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (v == p || vis[v])
            continue;
        root(v, u);
        siz[u] += siz[v];
        dp[u] = max(dp[u], siz[v]);
    }
    dp[u] = max(dp[u], sum - siz[u]);
    if (dp[u] < dp[rt])
        rt = u;
}
int tot, rev[N], dis[N] /* , pd[10000010] */;
void get_dis(int u, int p)
{
    rev[++tot] = dis[u];
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (v == p || vis[v])
            continue;
        dis[v] = dis[u] + val[i];
        get_dis(v, u);
    }
}
int q[N];
unordered_map<int, bool> pd;
void merge(int u)
{
    int top = 0;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (vis[v])
            continue;
        tot = 0, dis[v] = val[i], get_dis(v, u);
        for (int j = 1; j <= tot; j++)
            for (int k = 1; k <= m; k++)
                if (query[k] >= rev[j])
                    ans[k] |= pd[query[k] - rev[j]];
        for (int j = 1; j <= tot; j++)
            q[++top] = rev[j], pd[rev[j]] = true;
    }
    for (int i = 1; i <= top; i++)
        pd[q[i]] = false;
}
void solve(int u)
{
    vis[u] = pd[0] = true, merge(u);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (vis[v])
            continue;
        dp[0] = n, sum = siz[v], rt = 0;
        root(v, u), solve(rt);
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    dp[0] = sum = n = read(), m = read();
    for (int i = 1, u, v, w; i < n; i++)
        u = read(), v = read(), w = read(),
        contact(u, v, w), contact(v, u, w);
    for (int i = 1; i <= m; i++)
        query[i] = read();

    root(1, 0), solve(rt);

    for (int i = 1; i <= m; i++)
        puts(ans[i] ? "AYE" : "NAY");
    return 0;
}