#include <bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S = 1 << 24;
    char B[S], *H = B, *T = B;
    inline int gc() { return (H == T) && (T = (H = B) + fread(B, 1, S, stdin), H == T) ? EOF : *H++; }
    template <typename T = int>
    inline T input(T *p = nullptr)
    {
        static T *o = new T;
        !p && (p = o), *p = 0;
        int q = 1, c;
        while ((c = gc()) < '0' || c > '9')
            ;
        *p = c ^ '0';
        while ((c = gc()) >= '0' && c <= '9')
            *p = *p * 10 + (c ^ '0');
        return *p *= q;
    }
    template <typename T, typename... Args>
    inline void input(T *p, Args... args) { input(p), input(args...); }
}
using IO::input;

constexpr int N = 5e4 + 10;
int idx, head[N], edge[N << 1], nxt[N << 1];
inline void contact(int u, int v) { nxt[++idx] = head[u], head[u] = idx, edge[idx] = v; }

int fa[N], dep[N], siz[N], son[N];
void dfs1(int u)
{
    siz[u] = 1, dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        dfs1(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}

int tim, top[N], dfn[N];
void dfs2(int u, int t)
{
    top[u] = t, dfn[u] = ++tim;
    if (son[u])
        dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (v != son[u])
            dfs2(v, v);
    }
}

int rt[N];
namespace SEG
{
    struct
    {
        int ls, rs, tag;
        long long val, squ;
    } t[205 * N];
    int tot;

    inline void pushup(int p)
    {
        t[p].val = t[t[p].ls].val + t[t[p].rs].val;
        t[p].squ = t[t[p].ls].squ + t[t[p].rs].squ;
    }
    inline void spread(int &p, int l, int r, int v)
    {
        if (!p)
            p = ++tot;
        t[p].squ += 2ll * t[p].val * v + (r - l + 1ll) * v * v;
        t[p].val += (r - l + 1ll) * v;
        t[p].tag += v;
    }
    inline void pushdown(int p, int l, int r)
    {
        if (t[p].tag)
        {
            int mid = (l + r) >> 1;
            spread(t[p].ls, l, mid, t[p].tag);
            spread(t[p].rs, mid + 1, r, t[p].tag);
            t[p].tag = 0;
        }
    }

    int ql, qr, v;
    void update(int &p, int l, int r)
    {
        !p && (p = ++tot);
        if (ql <= l && r <= qr)
            return spread(p, l, r, v);

        int mid = (l + r) >> 1;
        pushdown(p, l, r);
        if (ql <= mid)
            update(t[p].ls, l, mid);
        if (qr > mid)
            update(t[p].rs, mid + 1, r);
        pushup(p);
    }
}

int n, c[N], f[N];
inline void update(int p, int col, int v)
{
    while (p)
        SEG::ql = dfn[top[p]], SEG::qr = dfn[p], SEG::v = v,
        SEG::update(rt[col], 1, n), p = fa[top[p]];
}

signed main()
{
    int m, q, C;
    input(&n, &m, &q, &C);
    for (int i = 1; i <= n; i++)
        input(c + i);
    for (int i = 2, p; i <= n; i++)
        input(&p), contact(fa[i] = p, i);
    for (int i = 1; i <= m; i++)
        input(f + i);
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; i++)
        update(i, c[i], 1);
    for (int i = 1, op, x, y; i <= q; i++)
    {
        input(&op, &x);
        if (op == 1)
            input(&y), update(x, c[x], -1), update(x, c[x] = y, 1);
        else
            printf("%.7lf\n", (1.0 * f[x] * f[x] * SEG::t[rt[x]].squ - 2.0 * f[x] * C * SEG::t[rt[x]].val) / n + 1ll * C * C);
    }
    return 0;
}