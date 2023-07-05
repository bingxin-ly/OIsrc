#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 5;
int n, m;
int idx, hed[N], edg[N << 1], val[N << 1], nxt[N << 1];
inline void contact(int u, int v, int w)
{
    nxt[++idx] = hed[u], hed[u] = idx;
    edg[idx] = v, val[idx] = w;
}

bool rmv[N];
int siz[N], pdis[N], qdis[N];
int size(int u, int p)
{
    if (rmv[u])
        return 0;
    int ret = 1;
    for (int i = hed[u]; i; i = nxt[i])
        if (edg[i] != p)
            ret += size(edg[i], u);
    return ret;
}
int gravct(int u, int p, int tot, int &gc) // gc: 在递归过程中求重心
{
    if (rmv[u])
        return 0;
    int sum = 1, maxs = 0;
    for (int i = hed[u]; i; i = nxt[i])
        if (edg[i] != p)
        {
            int siz = gravct(edg[i], u, tot, gc);
            maxs = max(maxs, siz);
            sum += siz;
        }
    maxs = max(maxs, tot - sum);
    if (maxs <= tot >> 1)
        gc = u;
    return sum;
}
void dist(int u, int p, int dis, int &len)
{
    if (rmv[u])
        return;
    qdis[len++] = dis;
    for (int i = hed[u]; i; i = nxt[i])
        if (edg[i] != p)
            dist(edg[i], u, dis + val[i], len);
}
inline int calc(int dis[], int len)
{
    sort(dis, dis + len);
    int ret = 0;
    for (int i = len - 1, j = -1; i >= 0; i--)
    {
        while (j + 1 < i && dis[j + 1] + dis[i] <= m)
            j++;
        j = min(j, i - 1), ret += j + 1;
    }
    return ret;
}
int solve(int u)
{
    if (rmv[u])
        return 0;
    int res = 0;
    gravct(u, -1, size(u, -1), u);
    rmv[u] = true;

    int plen = 0;
    for (int i = hed[u]; i; i = nxt[i])
    {
        int qlen = 0;
        dist(edg[i], -1, val[i], qlen);
        res -= calc(qdis, qlen);
        for (int k = 0; k < qlen; k++)
            res += qdis[k] <= m, pdis[plen++] = qdis[k];
    }
    res += calc(pdis, plen);
    for (int i = hed[u]; i; i = nxt[i])
        res += solve(edg[i]);
    return res;
}

signed main()
{
    while (scanf("%d%d", &n, &m), n || m)
    {
        idx = 0, memset(hed, 0, sizeof hed), memset(rmv, 0, sizeof rmv);
        for (int i = 0, u, v, w; i < n - 1; i++)
            scanf("%d%d%d", &u, &v, &w), contact(u, v, w), contact(v, u, w);
        printf("%d\n", solve(0));
    }
    return 0;
}