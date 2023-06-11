#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
struct segment_tree
{
    int ls, rs;
    int val, type;
} tr[80 * N];
int rt[N], tot;

inline void pushup(int p)
{
    if (tr[tr[p].ls].val >= tr[tr[p].rs].val)
        tr[p].val = tr[tr[p].ls].val, tr[p].type = tr[tr[p].ls].type;
    else
        tr[p].val = tr[tr[p].rs].val, tr[p].type = tr[tr[p].rs].type;
}
int update(int p, int l, int r, int pos, int v)
{
    if (!p)
        p = ++tot;
    if (l == r)
        return tr[p].val += v, tr[p].type = l, p;

    int mid = (l + r) >> 1;
    if (pos <= mid)
        tr[p].ls = update(tr[p].ls, l, mid, pos, v);
    else
        tr[p].rs = update(tr[p].rs, mid + 1, r, pos, v);
    pushup(p);
    return p;
}
int merge(int p, int q, int l, int r)
{
    if (!p || !q)
        return p ? p : q;
    if (l == r)
        return tr[p].val += tr[q].val, tr[p].type = l, p;

    int mid = (l + r) >> 1;
    tr[p].ls = merge(tr[p].ls, tr[q].ls, l, mid);
    tr[p].rs = merge(tr[p].rs, tr[q].rs, mid + 1, r);
    pushup(p);
    return p;
}

int idx, head[N], edge[N << 1], nxt[N << 1];
inline void contact(int u, int v)
{
    nxt[++idx] = head[u], head[u] = idx;
    edge[idx] = v;
}

int fa[N], dep[N], siz[N];
int son[N], top[N];
void dfs1(int u)
{
    son[u] = -1, siz[u] = 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (!dep[v])
        {
            dep[v] = dep[u] + 1, fa[v] = u;
            dfs1(v);
            siz[u] += siz[v];
            if (son[u] == -1 || siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}
void dfs2(int u, int t)
{
    top[u] = t;
    if (son[u] == -1)
        return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (v != son[u] && v != fa[u])
            dfs2(v, v);
    }
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

int r, x[N], y[N], z[N], ans[N];
void dfs3(int u)
{
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = edge[i];
        if (dep[v] > dep[u])
            dfs3(v), rt[u] = merge(rt[u], rt[v], 1, r);
    }
    if (tr[rt[u]].val)
        ans[u] = tr[rt[u]].type;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, contact(u, v), contact(v, u);
    dep[1] = 1, dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> x[i] >> y[i] >> z[i];
        r = max(r, z[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        int t = lca(x[i], y[i]);
        rt[x[i]] = update(rt[x[i]], 1, r, z[i], 1), rt[y[i]] = update(rt[y[i]], 1, r, z[i], 1);
        rt[t] = update(rt[t], 1, r, z[i], -1);
        if (fa[t])
            rt[fa[t]] = update(rt[fa[t]], 1, r, z[i], -1);
    }
    dfs3(1);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
    return 0;
}