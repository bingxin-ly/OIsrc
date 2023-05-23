#include <bits/stdc++.h>
using namespace std;

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

struct col
{
    int num, lc, rc;
    bool operator==(const col &otr) const { return num == otr.num && lc == otr.lc && rc == otr.rc; }
} const ZERO{0, 0, 0};
class segment_tree
{
    struct node
    {
        node *ls, *rs;
        int l, r, // 维护的左、右端点
            lazy;
        col val{};
        node(int _l, int _r, int col_ = 0) : l(_l), r(_r), lazy(0)
        {
            ls = rs = nullptr;
            val.num = 1, val.lc = val.rc = col_;
        }
    } *root;

    static void pushup(node *p)
    {
        assert(p->ls), assert(p->rs);
        p->val = {p->ls->val.num + p->rs->val.num - (p->ls->val.rc == p->rs->val.lc), p->ls->val.lc, p->rs->val.rc};
    }
    static void pushdown(node *p)
    {
        if (p->lazy)
        {
            p->ls->val = p->rs->val = {1, p->lazy, p->lazy};
            p->ls->lazy = p->rs->lazy = p->lazy;
            p->lazy = 0;
        }
    }

    void build(node *&p, int l, int r, const int *arr)
    {
        if (l == r)
            return p = new node(l, r, arr[l]), void();
        else
            p = new node(l, r);
        int mid = (l + r) >> 1;
        build(p->ls, l, mid, arr), build(p->rs, mid + 1, r, arr);
        pushup(p);
    }

    void update(node *p, int l, int r, int v)
    {
        if (l <= p->l && p->r <= r)
            return p->val.num = 1, p->val.lc = p->val.rc = p->lazy = v, void();
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

    col query(node *p, int l, int r)
    {
        if (!p)
            return ZERO;
        if (l <= p->l && p->r <= r)
            return p->val;

        pushdown(p);
        int mid = (p->l + p->r) >> 1;
        col lans = ZERO, rans = ZERO;
        if (l <= mid)
            lans = query(p->ls, l, r);
        if (r > mid)
            rans = query(p->rs, l, r);
        if (lans == ZERO || rans == ZERO)
            return lans == ZERO ? rans : lans;
        else
            return {lans.num + rans.num - (lans.rc == rans.lc), lans.lc, rans.rc};
    }

public:
    void build(int n, const int *arr) { build(root, 1, n, arr); }
    void update(int l, int r, int v) { update(root, l, r, v); }
    col query(int l, int r) { return query(root, l, r); }
} segtr;

int q_path(int u, int v)
{
    int tot = 0, ans1 = 0, ans2 = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v), swap(ans1, ans2);
        auto res = segtr.query(dfn[top[u]], dfn[u]);
        tot += res.num - (res.rc == ans1);
        ans1 = res.lc, u = fa[top[u]]; // 跳过轻边
    }
    if (dep[u] > dep[v])
        swap(u, v), swap(ans1, ans2);
    auto res = segtr.query(dfn[u], dfn[v]);
    tot += res.num - (ans1 == res.lc) - (ans2 == res.rc);
    return tot;
}

void u_path(int u, int v, int val)
{
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

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v,
            graph[u].push_back(v), graph[v].push_back(u);

    dep[1] = 1, dfs1(1), dfs2(1, 1);
    segtr.build(n, nw);
    while (m--)
    {
        char op;
        cin >> op;
        int a, b, c;
        if (op == 'Q')
        {
            cin >> a >> b;
            cout << q_path(a, b) << endl;
        }
        else
        {
            cin >> a >> b >> c;
            u_path(a, b, c);
        }
    }
    return 0;
}