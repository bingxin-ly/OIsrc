/* 边权：max(|a_u + a_v|, |a_u - a_v|)
   点权：|a_u| + |a_v| */
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int max(int a, int b) { return a > b ? a : b; }
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

const int N = 1e5 + 10;
vector<int> graph[N];

int fa[N], dep[N], siz[N];
int son[N], top[N], dfn[N];

void dfs1(int o)
{
    son[o] = -1, siz[o] = 1;
    for (auto v : graph[o])
        if (!dep[v])
        {
            dep[v] = dep[o] + 1, fa[v] = o;
            dfs1(v);
            siz[o] += siz[v];
            if (son[o] == -1 || siz[v] > siz[son[o]])
                son[o] = v;
        }
}

int cnt, w[N], nw[N];
void dfs2(int o, int t)
{
    top[o] = t, cnt++;
    dfn[o] = cnt, nw[cnt] = w[o];
    if (son[o] == -1)
        return;
    dfs2(son[o], t);
    for (auto v : graph[o])
        if (v != son[o] && v != fa[o])
            dfs2(v, v);
}

class BIT
{
    int size, *bit;

    inline static int lowbit(int x) { return x & -x; }
    inline int presum(int pos)
    {
        int res = 0;
        for (; pos; pos -= lowbit(pos))
            res += bit[pos];
        return res;
    }

public:
    inline void build(int size_, const int *src)
    {
        size = size_;
        bit = new int[size + 1]();
        int *sum = new int[size + 1]();
        for (int i = 1; i <= size; i++)
        {
            sum[i] = sum[i - 1] + src[i];
            bit[i] = sum[i] - sum[i - lowbit(i)];
        }
        delete[] sum;
    }

    inline void modify(int pos, int delta)
    {
        for (; pos <= size; pos += lowbit(pos))
            bit[pos] += delta;
    }

    inline int query(int l, int r)
    {
        return presum(r) - presum(l - 1);
    }

} tr;

inline int query_sum(int u, int v)
{
    int res = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        res += tr.query(dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    res += tr.query(dfn[u], dfn[v]);
    return res;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    int n = read(), q = read();
    for (int i = 1; i <= n; i++)
        w[i] = read();
    for (int i = 1, a, b; i < n; i++)
        a = read(), b = read(), graph[a].push_back(b), graph[b].push_back(a);

    dep[1] = 1, dfs1(1), dfs2(1, 1);
    tr.build(n, nw);

    while (q--)
    {
        int op = read(), a = read(), b = read();
        if (op == 1)
            tr.modify(dfn[a], b - w[a]), w[a] = b;
        else
            printf("%lld\n", 2 * query_sum(a, b) - w[a] - w[b]);
    }
    return 0;
}