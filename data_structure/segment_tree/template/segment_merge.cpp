#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn 100005
#define M 6000005
#define LL long long
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
inline int read()
{
    char c = getchar();
    int x = 0;
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        x = (x << 3) + (x << 1) + c - 48, c = getchar();
    return x;
}
struct E
{
    int v, nxt;
} e[maxn << 1];
int l[M], r[M], d[M], t[M];
int top[maxn], fa[maxn], head[maxn], deep[maxn], son[maxn], sum[maxn], X[maxn], Y[maxn], Z[maxn], Ans[maxn];
int n, m, rt[maxn], cnt, R, num;
inline void add(int x, int y)
{
    e[++num].v = y;
    e[num].nxt = head[x];
    head[x] = num;
}
void dfs1(int x)
{
    sum[x] = 1;
    int maxx = -1;
    for (int i = head[x]; i; i = e[i].nxt)
        if (!deep[e[i].v])
        {
            deep[e[i].v] = deep[x] + 1, fa[e[i].v] = x;
            dfs1(e[i].v);
            sum[x] += sum[e[i].v];
            if (sum[e[i].v] > maxx)
                maxx = sum[e[i].v], son[x] = e[i].v;
        }
}
void dfs2(int x, int topf)
{
    top[x] = topf;
    if (!son[x])
        return;
    dfs2(son[x], topf);
    for (int i = head[x]; i; i = e[i].nxt)
        if (!top[e[i].v])
            dfs2(e[i].v, e[i].v);
}
inline int LCA(int x, int y)
{
    while (top[x] != top[y])
    {
        if (deep[top[x]] < deep[top[y]])
            std::swap(x, y);
        x = fa[top[x]];
    }
    if (deep[x] < deep[y])
        return x;
    return y;
}
inline void pushup(int a)
{
    if (d[l[a]] >= d[r[a]])
        d[a] = d[l[a]], t[a] = t[l[a]];
    else
        d[a] = d[r[a]], t[a] = t[r[a]];
}
int change(int a, int x, int y, int pos, int val)
{
    if (!a)
        a = ++cnt;
    if (x == y)
    {
        d[a] += val, t[a] = x;
        return a;
    }
    int mid = x + y >> 1;
    if (pos <= mid)
        l[a] = change(l[a], x, mid, pos, val);
    else
        r[a] = change(r[a], mid + 1, y, pos, val);
    pushup(a);
    return a;
}
int merge(int a, int b, int x, int y)
{
    if (!a)
        return b;
    if (!b)
        return a;
    if (x == y)
    {
        d[a] += d[b];
        t[a] = x;
        return a;
    }
    int mid = x + y >> 1;
    l[a] = merge(l[a], l[b], x, mid), r[a] = merge(r[a], r[b], mid + 1, y);
    pushup(a);
    return a;
}
void Redfs(int x)
{
    for (int i = head[x]; i; i = e[i].nxt)
        if (deep[e[i].v] > deep[x])
            Redfs(e[i].v), rt[x] = merge(rt[x], rt[e[i].v], 1, R);
    if (d[rt[x]])
        Ans[x] = t[rt[x]];
}
int main()
{
    n = read(), m = read();
    int x, y, z;
    for (int i = 1; i < n; i++)
        x = read(), y = read(), add(y, x), add(x, y);
    deep[1] = 1, dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= m; i++)
        X[i] = read(), Y[i] = read(), Z[i] = read(), R = max(R, Z[i]);
    for (int i = 1; i <= m; i++)
    {
        int lca = LCA(X[i], Y[i]);
        rt[X[i]] = change(rt[X[i]], 1, R, Z[i], 1), rt[Y[i]] = change(rt[Y[i]], 1, R, Z[i], 1);
        rt[lca] = change(rt[lca], 1, R, Z[i], -1);
        if (fa[lca])
            rt[fa[lca]] = change(rt[fa[lca]], 1, R, Z[i], -1);
    }
    Redfs(1);
    for (int i = 1; i <= n; i++)
        printf("%d\n", Ans[i]);
    return 0;
}
