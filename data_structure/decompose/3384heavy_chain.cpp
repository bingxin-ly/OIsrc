#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 1e5 + 10;
int n, m, r, mod;
vector<int> g[N];

int fa[N], dep[N], siz[N], son[N];
void dfs1(int u, int p) {
    fa[u] = p, dep[u] = dep[p] + 1, siz[u] = 1;
    for (int v : g[u])
        if (v != p) {
            dfs1(v, u), siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
}

int idx, dfn[N], top[N], w[N], nw[N];
void dfs2(int u, int t) {
    top[u] = t, dfn[u] = ++idx, nw[idx] = w[u];
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int v : g[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}

struct {
    int val, tag;
} t[N << 2];
#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p) { t[p].val = (t[ls].val + t[rs].val) % mod; }
void pushtag(int p, int l, int r, int v) {
    t[p].val += (r - l + 1) * v % mod, t[p].val %= mod;
    t[p].tag += v, t[p].tag %= mod;
}
void pushdown(int p, int l, int r) {
    if (t[p].tag) {
        int m = (l + r) >> 1;
        pushtag(ls, l, m, t[p].tag), pushtag(rs, m + 1, r, t[p].tag);
        t[p].tag = 0;
    }
}
void build(int p, int l, int r) {
    if (l == r) return t[p].val = nw[l], void();
    int m = (l + r) >> 1;
    build(ls, l, m), build(rs, m + 1, r);
    pushup(p);
}
void update(int p, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) return pushtag(p, l, r, v);
    pushdown(p, l, r);
    int m = (l + r) >> 1;
    if (ql <= m) update(ls, l, m, ql, qr, v);
    if (qr > m) update(rs, m + 1, r, ql, qr, v);
    pushup(p);
}
int query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return t[p].val;
    pushdown(p, l, r);
    int m = (l + r) >> 1, ret = 0;
    if (ql <= m) ret += query(ls, l, m, ql, qr);
    if (qr > m) ret += query(rs, m + 1, r, ql, qr), ret %= mod;
    return ret;
}

int q_path(int u, int v) {
    int tot = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        tot += query(1, 1, n, dfn[top[u]], dfn[u]), tot %= mod;
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    tot += query(1, 1, n, dfn[u], dfn[v]), tot %= mod;
    return tot;
}

void u_path(int u, int v, int val) {
    val %= mod;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(1, 1, n, dfn[top[u]], dfn[u], val);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    update(1, 1, n, dfn[u], dfn[v], val);
}

int q_son(int u) { return query(1, 1, n, dfn[u], dfn[u] + siz[u] - 1); }
void u_son(int u, int k) { update(1, 1, n, dfn[u], dfn[u] + siz[u] - 1, k); }

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> r >> mod;
    for (int i = 1; i <= n; i++)
        cin >> w[i], w[i] %= mod;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);

    dfs1(r, 0), dfs2(r, r), build(1, 1, n);
    while (m--) {
        int op, x, y, z;
        cin >> op;
        switch (op) {
            case 1:
                cin >> x >> y >> z;
                u_path(x, y, z);
                break;
            case 2:
                cin >> x >> y;
                cout << q_path(x, y) << '\n';
                break;
            case 3:
                cin >> x >> z;
                u_son(x, z);
                break;
            case 4:
                cin >> x;
                cout << q_son(x) << '\n';
                break;
        }
    }
    return 0;
}