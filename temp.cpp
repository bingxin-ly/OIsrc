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

const int N = 4e4 + 10;
struct edge
{
    int v, w, next;
} e[N << 1];
int n, m, head[N], cnt, k, ans;
int dp[N], vis[N], sum, dis[N], rt, siz[N], rev[N], tot;
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, head[u]}, head[u] = cnt;
    e[++cnt] = {u, w, head[v]}, head[v] = cnt;
}
inline void getrt(int u, int p)
{
    siz[u] = 1, dp[u] = 0;
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if (v == p || vis[v])
            continue;
        getrt(v, u);
        siz[u] += siz[v];
        dp[u] = max(dp[u], siz[v]);
    }
    dp[u] = max(dp[u], sum - siz[u]);
    if (dp[u] < dp[rt])
        rt = u;
}
inline void getdis(int u, int p)
{
    rev[++tot] = dis[u];
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if (v == p || vis[v])
            continue;
        dis[v] = dis[u] + e[i].w;
        getdis(v, u);
    }
}
inline int doit(int u, int w)
{
    tot = 0, dis[u] = w, getdis(u, 0);
    sort(rev + 1, rev + tot + 1);
    int l = 1, r = tot, res = 0;
    while (l <= r)
        (rev[l] + rev[r] <= k) ? (res += r - l, ++l) : (--r);
    return res;
}
inline void solve(int u)
{
    vis[u] = 1, ans += doit(u, 0);
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if (vis[v])
            continue;
        ans -= doit(v, e[i].w);
        sum = siz[v], dp[0] = n, rt = 0;
        getrt(v, u), solve(rt);
    }
}
int main()
{
    dp[0] = sum = n = read();
    for (int i = 1; i <= n - 1; ++i)
    {
        int u = read(), v = read(), w = read();
        add(u, v, w);
    }
    k = read(), getrt(1, 0), solve(rt);
    printf("%d", ans);
    return 0;
}
