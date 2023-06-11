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

const int N = 2e4 + 10;
int idx, head[N], edge[N << 1], val[N << 1], nxt[N << 1];
inline void contact(int u, int v, int w)
{
    nxt[++idx] = head[u], head[u] = idx;
    edge[idx] = v, val[idx] = w;
}

bool vis[N];
int rt, sum, dp[N], siz[N];
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

int t[3], dis[N];
void deep(int u, int p)
{
    t[dis[u]]++;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (v == p || vis[v])
            continue;
        dis[v] = (dis[u] + val[i]) % 3;
        deep(v, u);
    }
}

int ans;
int calc(int u, int x)
{
    memset(t, 0, sizeof t), dis[u] = x;
    deep(u, 0);
    return 2 * t[1] * t[2] + t[0] * t[0];
}
void solve(int u)
{
    ans += calc(u, 0), vis[u] = true;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (vis[v])
            continue;
        ans -= calc(v, val[i]);
        rt = 0, sum = siz[v];
        root(v, 0), solve(rt);
    }
}

signed main()
{
    int n = read();
    for (int i = 1; i < n; i++)
    {
        int u = read(), v = read(), w = read() % 3;
        contact(u, v, w), contact(v, u, w);
    }

    sum = dp[0] = n;
    root(1, 0), solve(rt);

    int tt = __gcd(ans, n * n);
    printf("%d/%d", ans / tt, n * n / tt);
    return 0;
}