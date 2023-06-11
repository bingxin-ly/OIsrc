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

const int N = 1e4 + 10, M = 110;
int idx, head[N], to[N << 1], val[N << 1], nxt[N << 1];
inline void contact(int u, int v, int w)
{
    nxt[++idx] = head[u], head[u] = idx,
    to[idx] = v, val[idx] = w;
}

long long dis[N];
int siz[N], son[N];
void dfs1(int u, int p)
{
    siz[u] = 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == p)
            continue;
        dis[v] = dis[u] + val[i];
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}

bool ans[M];
int n, m, ask[M];
unordered_set<long long> exist;

void upd(int u, int p, bool op)
{
    if (op)
        exist.insert(dis[u]);
    else
        exist.erase(dis[u]);

    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != p)
            upd(v, u, op);
    }
}
void calc(int u, int p, int rt)
{
    for (int i = 1; i <= m; i++)
    {
        long long c = ask[i] + (dis[rt] << 1) - dis[u];
        ans[i] |= exist.count(c);
    }

    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != p)
            calc(v, u, rt);
    }
}
void dfs2(int u, int p, bool keep)
{
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != p && v != son[u])
            dfs2(v, u, false);
    }
    if (son[u])
        dfs2(son[u], u, true);

    for (int i = 1; i <= m; i++)
        ans[i] |= exist.count(dis[u] + ask[i]);
    exist.insert(dis[u]);

    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != p && v != son[u])
            calc(v, u, u), upd(v, u, true);
    }

    if (!keep)
        upd(u, p, false);
}

signed main()
{
    n = read(), m = read();
    for (int i = 1, u, v, w; i < n; i++)
        u = read(), v = read(), w = read(), contact(u, v, w), contact(v, u, w);
    for (int i = 1; i <= m; i++)
        ask[i] = read();

    dfs1(1, 0);
    dfs2(1, 0, true);

    for (int i = 1; i <= m; i++)
        puts(ans[i] ? "AYE" : "NAY");
    return 0;
}