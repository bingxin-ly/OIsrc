#include <bits/stdc++.h>
using namespace std;
inline int max(int a, int b) { return a > b ? a : b; }
inline int read()
{
    int o = 1, p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            o = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0',
        c = getchar();
    return o * p;
}

const int N = 3e4 + 10;
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

class segment_tree
{
    struct node
    {
        node *ls, *rs;
        int l, r;
        int val, maxn;

        node(int l_, int r_, int val_ = 0) : l(l_), r(r_)
        {
            val = maxn = val_;
            ls = rs = nullptr;
        }
    } *root;

    inline static void pushup(node *p)
    {
        p->val = (p->ls ? p->ls->val : 0) + (p->rs ? p->rs->val : 0);
        p->maxn = max(p->ls->maxn, p->rs->maxn);
    }

    void build(node *&p, int l, int r, const int *ori)
    {
        if (l == r)
            return p = new node(l, r, ori[l]), void();
        else
            p = new node(l, r);
        int mid = (l + r) >> 1;
        build(p->ls, l, mid, ori), build(p->rs, mid + 1, r, ori);
        pushup(p);
    }

    void modify(node *p, int pos, int val)
    {
        if (p->l == p->r)
        {
            assert(p->l == pos);
            p->maxn = p->val = val;
            return;
        }
        int mid = (p->l + p->r) >> 1;
        if (pos <= mid)
        {
            if (!p->ls)
                p->ls = new node(p->l, mid);
            modify(p->ls, pos, val);
        }
        else
        {
            if (!p->rs)
                p->rs = new node(mid + 1, p->r);
            modify(p->rs, pos, val);
        }
        pushup(p);
    }

    int query_sum(node *p, int l, int r)
    {
        if (!p)
            return 0;
        if (l <= p->l && p->r <= r)
            return p->val;

        int mid = (p->l + p->r) >> 1, ans = 0;
        if (l <= mid)
            ans += query_sum(p->ls, l, r);
        if (r > mid)
            ans += query_sum(p->rs, l, r);
        return ans;
    }

    int query_peak(node *p, int l, int r)
    {
        if (!p)
            return INT_MIN;
        if (l <= p->l && p->r <= r)
            return p->maxn;

        int mid = (p->l + p->r) >> 1, ans = INT_MIN;
        if (l <= mid)
            ans = max(ans, query_peak(p->ls, l, r));
        if (r > mid)
            ans = max(ans, query_peak(p->rs, l, r));
        return ans;
    }

public:
    inline void build(int n, const int *ori) { build(root, 1, n, ori); }
    inline void modify(int pos, int val) { modify(root, pos, val); }
    inline int query_sum(int l, int r) { return query_sum(root, l, r); }
    inline int query_peak(int l, int r) { return query_peak(root, l, r); }
} segtr;

int query_sum(int u, int v)
{
    int res = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        res += segtr.query_sum(dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    res += segtr.query_sum(dfn[u], dfn[v]);
    return res;
}

int query_peak(int u, int v)
{
    int res = INT_MIN;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        res = max(res, segtr.query_peak(dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    res = max(res, segtr.query_peak(dfn[u], dfn[v]));
    return res;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    int n = read();
    for (int i = 1, a, b; i < n; i++)
        a = read(), b = read(), graph[a].push_back(b), graph[b].push_back(a);

    for (int i = 1; i <= n; i++)
        w[i] = read();
    dep[1] = 1, fa[1] = 1, dfs1(1), dfs2(1, 1);
    segtr.build(n, nw);

    int q = read();
    while (q--)
    {
        char opt[10];
        scanf("%s", opt);
        int a = read(), b = read();
        switch (opt[1])
        {
        case 'S':
            printf("%d\n", query_sum(a, b));
            break;
        case 'M':
            printf("%d\n", query_peak(a, b));
            break;
        case 'H':
            segtr.modify(dfn[a], b);
            break;
        }
    }
    return 0;
}