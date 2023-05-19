#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<int> graph[N];

int fa[N], dep[N], siz[N];          // normal
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

int cnt, w[N], nw[N];
void dfs2(int o, int t) // decomposition
{
    top[o] = t, cnt++;
    dfn[o] = cnt, rnk[cnt] = o, nw[cnt] = w[o];
    if (son[o] == -1)
        return;
    dfs2(son[o], t);
    for (auto v : graph[o])
        if (v != son[o] && v != fa[o])
            dfs2(v, v);
}

int lca(int u, int v)
{
    while (top[u] != top[v])
        if (dep[top[u]] > dep[top[v]])
            u = fa[top[u]];
        else
            v = fa[top[v]];
    return dep[u] > dep[v] ? v : u;
}

int mod;
class segment_tree
{
    struct node
    {
        node *ls, *rs;
        int l, r, // 维护的左、右端点
            val, lazy;
        explicit node(int _l = 0, int _r = 0, int _val = 0) : l(_l), r(_r), val(_val), lazy(0)
        {
            ls = rs = nullptr;
        }
    } *root;

    static void pushup(node *p)
    {
        p->val = (p->ls ? p->ls->val : 0) + (p->rs ? p->rs->val : 0);
        p->val %= mod;
    }
    static void pushdown(node *p)
    {
        if (p->lazy)
        {
            int mid = (p->l + p->r) >> 1;
            p->ls->val += (mid - p->l + 1) * p->lazy, p->ls->val %= mod;
            p->rs->val += (p->r - mid) * p->lazy, p->rs->val %= mod;

            p->ls->lazy += p->lazy, p->rs->lazy += p->lazy;
            p->lazy = 0;
        }
    }

    void build(node *&p, int l, int r, const int *arr)
    {
        p = new node(l, r);
        if (l == r)
        {
            p->val = arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p->ls, l, mid, arr), build(p->rs, mid + 1, r, arr);
        pushup(p);
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
        return ans % mod;
    }

public:
    void build(int n, const int *arr) { build(root, 1, n, arr); }
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
        tot += segtr.query(dfn[top[u]], dfn[u]), tot %= mod;
        u = fa[top[u]]; // 跳过轻边
    }
    if (dep[u] > dep[v])
        swap(u, v);
    tot += segtr.query(dfn[u], dfn[v]), tot %= mod;
    return tot;
}

void u_path(int u, int v, int val)
{
    val %= mod;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        segtr.update(dfn[top[u]], dfn[u], val);
        u = fa[top[u]]; // 跳过轻边
    }
    if (dep[u] > dep[v])
        swap(u, v);
    segtr.update(dfn[u], dfn[v], val);
}

int q_son(int u) { return segtr.query(dfn[u], dfn[u] + siz[u] - 1); }

void u_son(int u, int k) { segtr.update(dfn[u], dfn[u] + siz[u] - 1, k); }

int main()
{
    int n, m, r;
    cin >> n >> m >> r >> mod;
    for (int i = 1; i <= n; i++)
        cin >> w[i], w[i] %= mod;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v,
            graph[u].push_back(v), graph[v].push_back(u);

    dep[r] = 1, dfs1(r), dfs2(r, r);
    segtr.build(n, nw);
    while (m--)
    {
        int op, x, y, z;
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> x >> y >> z;
            u_path(x, y, z);
            break;
        case 2:
            cin >> x >> y;
            cout << q_path(x, y) << endl;
            break;
        case 3:
            cin >> x >> z;
            u_son(x, z);
            break;
        case 4:
            cin >> x;
            cout << q_son(x) << endl;
            break;
        }
    }
    return 0;
}