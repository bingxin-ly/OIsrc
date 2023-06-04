#include <bits/stdc++.h>
using namespace std;

const int N = 8e5 + 10;
vector<int> graph[N];

int fa[N], dep[N], siz[N];  // normal
int son[N], top[N], dfn[N], rnk[N]; // decomposition

void dfs1(int o) // build
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

int tim;
void dfs2(int o, int t) // decomposition
{
    top[o] = t, dfn[o] = ++tim, rnk[tim] = o;
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
        int l, r, // 维护的左、右端点
            val, lazy;
        node(int _l, int _r, int _val = 0) : l(_l), r(_r), val(_val), lazy(0)
        {
            ls = rs = nullptr;
        }
    } *root;

    static void pushup(node *p)
    {
        p->val = (p->ls ? p->ls->val : 0) + (p->rs ? p->rs->val : 0);
    }
    static void pushdown(node *p)
    {
        if (p->lazy)
        {
            int mid = (p->l + p->r) >> 1;
            if (!p->ls)
                p->ls = new node(p->l, mid);
            if (!p->rs)
                p->rs = new node(mid + 1, p->r);

            p->ls->val += (mid - p->l + 1) * p->lazy;
            p->rs->val += (p->r - mid) * p->lazy;

            p->ls->lazy += p->lazy, p->rs->lazy += p->lazy;
            p->lazy = 0;
        }
    }

    void update(node *p, int l, int r, int v)
    {
        if (l <= p->l && p->r <= r)
        {
            p->val += (p->r - p->l + 1) * v;
            p->lazy += v;
            return;
        }
        pushdown(p);
        int mid = (p->l + p->r) >> 1;
        if (l <= mid)
        {
            if (!p->ls)
                p->ls = new node(p->l, mid);
            update(p->ls, l, r, v);
        }
        if (r > mid)
        {
            if (!p->rs)
                p->rs = new node(mid + 1, p->r);
            update(p->rs, l, r, v);
        }
        pushup(p);
    }

    int query(node *p, int l, int r)
    {
        if (!p)
            return 0;
        if (l <= p->l && p->r <= r)
            return p->val;

        pushdown(p);
        int mid = (p->l + p->r) >> 1;
        int ans = 0;
        if (l <= mid)
            ans += query(p->ls, l, r);
        if (r > mid)
            ans += query(p->rs, l, r);
        return ans;
    }

public:
    void build(int n) { root = new node(1, n); }
    void update(int l, int r, int v) { update(root, l, r, v); }
    int query(int l, int r) { return query(root, l, r); }
} segtr;

int q_path(int u, int v)
{
    int tot = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        tot += segtr.query(dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    tot += segtr.query(dfn[u], dfn[v]);
    return tot;
}
void u_path(int u, int v, int val)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        segtr.update(dfn[top[u]], dfn[u], val);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    segtr.update(dfn[u], dfn[v], val);
}

int n, w[N];
int solve(int x)
{
    if (!segtr.query(1, n))
        return 0;
    int c = segtr.query(dfn[x], dfn[x]);
    while (!c && x != 1)
    {
        x = fa[x];
        c = segtr.query(dfn[x], dfn[x]);
    }
    return x;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int q;
    cin >> n >> q;
    for (int i = 2, f; i <= n; i++)
        cin >> f,
            graph[f].emplace_back(i), graph[i].emplace_back(f);

    dep[1] = 1, dfs1(1), dfs2(1, 1);
    segtr.build(n);

    for (int x; q--;)
    {
        cin >> x;
        if (x > 0)
            u_path(1, x, w[x] ? -1 : 1), w[x] = !w[x];
        else
            cout << solve(-x) << endl;
    }
    return 0;
}