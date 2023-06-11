#include <bits/stdc++.h>
using namespace std;
inline int rd()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

const int N = 2e5 + 10, INF = 0x3f3f3f3f;
int idx, head[N], to[N << 1], val[N << 1], nxt[N << 1];
inline void add(int u, int v, int w)
{
    nxt[++idx] = head[u], head[u] = idx,
    to[idx] = v, val[idx] = w;
}

long long dis[N];
int dep[N], siz[N], son[N];
void dfs1(int u, int p)
{
    siz[u] = 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == p)
            continue;
        dep[v] = dep[u] + 1;
        dis[v] = dis[u] + val[i];
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}

int n, k, res;
unordered_map<long long, int> minn;

void upd(int u, int p, bool op)
{
    if (op)
    {
        if (minn.count(dis[u]))
            minn[dis[u]] = min(minn[dis[u]], dep[u]);
        else
            minn[dis[u]] = dep[u];
    }
    else
        minn[dis[u]] = INF;

    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v != p)
            upd(v, u, op);
    }
}
void calc(int u, int p, int rt)
{
    long long c = k + (dis[rt] << 1) - dis[u];
    if (minn.count(c))
        res = min(res, minn[c] + dep[u] - (dep[rt] << 1));

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

    if (minn.count(dis[u] + k))
        res = min(res, minn[dis[u] + k] - dep[u]);
    minn[dis[u]] = dep[u];

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
    n = rd(), k = rd();
    for (int i = 1, u, v, w; i < n; i++)
        u = rd() + 1, v = rd() + 1, w = rd(), add(u, v, w), add(v, u, w);

    dfs1(1, 0);
    res = N;
    dfs2(1, 0, true);

    printf("%d", res == N ? -1 : res);
    return 0;
}