#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 5;
int n, m, q, k;
vector<int> g[N];

int tim, dfn[N], low[N], top, stk[N], vis[N], cnt, col[N], siz[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++tim, stk[++top] = u, vis[u] = 1;
    for (int v : g[u])
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    if (low[u] == dfn[u])
    {
        col[u] = ++cnt;
        while (stk[top] != u)
            col[stk[top]] = cnt, vis[stk[top--]] = 0;
        vis[stk[top--]] = 0;
    }
}

int fa[N], dep[N], anc[20][N], sbt[N];
int shallow(int u, int v) { return dep[u] < dep[v] ? u : v; }
bool ances(int u, int v) { return dfn[u] <= dfn[v] && dfn[u] + sbt[u] > dfn[v]; }
void dfs(int u, int p)
{
    dfn[u] = ++tim, anc[0][tim] = p, dep[u] = dep[p] + siz[u];
    sbt[u] = 1;
    for (int v : g[u])
        dfs(v, u), sbt[u] += sbt[v];
}

int p[6], vsp[6], pos[6][6], vsr[6], rev[6][6];
void mark(int u, int vs[], int g[][6])
{
    vs[u] = 1;
    for (int v = 0; v < 6; v++)
        if (g[u][v] && !vs[v])
            mark(v, vs, g);
}
int lca(int u, int v)
{
    if (u == v)
        return u;
    if ((u = dfn[u]) > (v = dfn[v]))
        swap(u, v);
    int d = __lg(v - u++);
    return shallow(anc[d][u], anc[d][v - (1 << d) + 1]);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> q >> k;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v);

    // 原图跑 SCC 缩点
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);

    // 根据题目性质，将缩后的 DAG 抽成一棵树
    memset(fa, 0x3f, sizeof(fa));
    for (int u = 1; u <= n; u++)
    {
        siz[col[u]] += 1;
        for (int v : g[u])
            if (col[u] != col[v])
                fa[col[v]] = min(fa[col[v]], col[u]);
        g[u].clear();
    }
    for (int i = 1; i < cnt; i++)
        g[fa[i]].emplace_back(i);

    tim = 0, dfs(cnt, 0);
    for (int i = 1; i <= __lg(cnt); i++)
        for (int j = 1; j + (1 << i) - 1 <= cnt; j++)
            anc[i][j] = shallow(anc[i - 1][j], anc[i - 1][j + (1 << (i - 1))]);

    k = (k + 1) << 1;
    while (q--)
    {
        memset(vsp, 0, sizeof(vsp)), memset(vsr, 0, sizeof(vsr));
        memset(pos, 0, sizeof(pos)), memset(rev, 0, sizeof(rev)), memset(p, 0, sizeof(p));

        for (int i = 0; i < k; i++)
            cin >> p[i], p[i] = col[p[i]];
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++)
                if (ances(p[i], p[j]))
                    pos[i][j] = rev[j][i] = 1;
        for (int i = 2; i < k; i += 2)
            pos[i][i + 1] = rev[i + 1][i] = 1;
        mark(0, vsp, pos), mark(1, vsr, rev);

        vector<int> q;
        for (int i = 0; i < k; i++)
            if (vsp[i] && vsr[i])
                q.emplace_back(p[i]);
        if (q.empty())
        {
            cout << "0\n";
            continue;
        }

        int ans = 0;
        sort(q.begin(), q.end(), [](int u, int v)
             { return dfn[u] < dfn[v]; });
        q.resize(unique(q.begin(), q.end()) - q.begin());
        for (int i : q)
            ans += siz[i];
        auto calc = [&ans](int u, int v)
        { ans += dep[v] - dep[u] - siz[v]; };
        stk[top = 1] = q[0];
        for (int i = 1; i < (int)q.size(); i++)
        {
            int t = lca(q[i - 1], q[i]);
            while (top > 1 && dep[t] <= dep[stk[top - 1]])
                calc(stk[top - 1], stk[top]), top--;
            if (t != stk[top])
            {
                if (top == 1)
                    top = 0;
                else
                    ans += siz[t], calc(t, stk[top]), stk[top] = t;
            }
            stk[++top] = q[i];
        }
        for (int i = 1; i < top; i++)
            calc(stk[i], stk[i + 1]);
        cout << ans << '\n';
    }
    return 0;
}