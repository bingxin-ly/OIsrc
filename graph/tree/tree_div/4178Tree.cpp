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
int idx, head[N], edge[N << 1], val[N << 1], nxt[N << 1];
inline void contact(int u, int v, int w)
{
    nxt[++idx] = head[u], head[u] = idx,
    edge[idx] = v, val[idx] = w;
}

int n, k, rt, sum, ans;
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
int tot, rev[N], dis[N];
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
int merge(int u, int w)
{
    tot = 0, dis[u] = w, get_dis(u, 0);
    sort(rev + 1, rev + tot + 1);
    int res = 0;
    for (int l = 1, r = tot; l <= r;)
    {
        if (rev[l] + rev[r] <= k)
            res += r - l, l++;
        else
            r--;
    }
    return res;
}
void solve(int u)
{
    vis[u] = 1, ans += merge(u, 0);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (vis[v])
            continue;
        ans -= merge(v, val[i]);
        dp[0] = n, sum = siz[v], rt = 0;
        root(v, u), solve(rt);
    }
}

signed main()
{
    dp[0] = sum = n = read();
    for (int i = 1, u, v, w; i < n; i++)
        u = read(), v = read(), w = read(),
        contact(u, v, w), contact(v, u, w);

    k = read(), root(1, 0), solve(rt);

    printf("%d", ans);
    return 0;
}