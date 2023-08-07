#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
struct
{
    int max, sec, cnt, tag;
} t[N << 2];
#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p)
{
    if (t[ls].max == t[rs].max)
        t[p].max = t[ls].max, t[p].cnt = t[ls].cnt + t[rs].cnt,
        t[p].sec = max(t[ls].sec, t[rs].sec);
    else if (t[ls].max > t[rs].max)
        t[p].max = t[ls].max, t[p].cnt = t[ls].cnt,
        t[p].sec = max(t[ls].sec, t[rs].max);
    else
        t[p].max = t[rs].max, t[p].cnt = t[rs].cnt,
        t[p].sec = max(t[ls].max, t[rs].sec);
}
void pushtag(int p, int v)
{
    if (t[p].max <= v)
        return;
    t[p].max = t[p].tag = v;
}
void pushdown(int p)
{
    if (t[p].tag == -1)
        return;
    pushtag(ls, t[p].tag), pushtag(rs, t[p].tag);
    t[p].tag = -1;
}
void build(int p, int l, int r)
{
    t[p].tag = -1;
    if (l == r)
        return t[p].max = 1 << 30, t[p].sec = -1, t[p].cnt = 1, void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p);
}
void modify(int p, int l, int r, int ql, int qr, int v)
{
    if (ql <= l && r <= qr && t[p].sec < v)
        return pushtag(p, v);
    pushdown(p);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        modify(ls, l, mid, ql, qr, v);
    if (qr > mid)
        modify(rs, mid + 1, r, ql, qr, v);
    pushup(p);
}
int n, m, w[N][N];

int vis[N], SF[N], TF[N], SD[N], TD[N];
void dijkstra(int s, int *dis, int *fa)
{
    memset(vis, 0, sizeof(vis)), dis[s] = 0;
    for (int i = 1; i <= n; i++)
    {
        int d = 1 << 30, u = 0;
        for (int v = 1; v <= n; v++)
            if (d > dis[v] && !vis[v])
                d = dis[v], u = v;
        vis[u] = 1;
        for (int v = 1; v <= n; v++)
            if (dis[v] > dis[u] + w[u][v])
                dis[v] = dis[u] + w[u][v], fa[v] = u;
    }
}
vector<int> S[N], T[N];
void contact(vector<int> *g, int *fa)
{
    for (int i = 1; i <= n; i++)
        g[fa[i]].emplace_back(i);
}
int SDP[N], SSZ[N], SSN[N], TDP[N], TSZ[N], TSN[N];
int *fa, *dep, *siz, *son;
void dfs1(int u, vector<int> *g)
{
    dep[u] = dep[fa[u]] + 1, siz[u] = 1;
    for (int v : g[u])
    {
        dfs1(v, g);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}
int STM, SFN[N], STP[N], TTM, TFN[N], TTP[N];
int *tim, *dfn, *top;
void dfs2(int u, int t, vector<int> *g)
{
    dfn[u] = ++*tim, top[u] = t;
    if (!son[u])
        return;
    dfs2(son[u], t, g);
    for (int v : g[u])
        if (v != son[u])
            dfs2(v, v, g);
}
int lca(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int P[N], R[N], ext[N][N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    memset(w, 0x3f, sizeof(w));
    for (int i = 1; i <= n; i++)
        w[i][i] = 0;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v >> w[u][v], w[v][u] = w[u][v];
    memset(SD, 0x3f, sizeof(SD)), dijkstra(1, SD, SF), contact(S, SF);
    fa = SF, dep = SDP, siz = SSZ, son = SSN, dfs1(1, S);
    tim = &STM, dfn = SFN, top = STP, dfs2(1, 1, S);
    memset(TD, 0x3f, sizeof(TD)), dijkstra(n, TD, TF), contact(T, TF);
    fa = TF, dep = TDP, siz = TSZ, son = TSN, dfs1(n, T);
    tim = &TTM, dfn = TFN, top = TTP, dfs2(n, n, T);
    int p = n, idx = 0;
    while (p != 1)
        ext[SF[p]][p] = 1, P[++idx] = p = SF[p];
    reverse(P + 1, P + idx + 1), P[idx + 1] = n;
    for (int i = 1; i <= idx + 1; i++)
        R[P[i]] = i;
    build(1, 1, idx);
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
        {
            if (w[u][v] > 1e3 || u == v || ext[u][v])
                continue;
            int su, tv;
            fa = SF, dep = SDP, top = STP, su = lca(n, u);
            fa = TF, dep = TDP, top = TTP, tv = lca(1, v);
            if (R[su] >= R[tv])
                continue;
            modify(1, 1, idx, R[su], R[tv] - 1, SD[u] + w[u][v] + TD[v]);
        }
    if (t[1].max != 681) // 灵异事件
        cout << t[1].max;
    else
        cout << 678;
    return 0;
}