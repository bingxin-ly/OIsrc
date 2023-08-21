#include <bits/stdc++.h>
using namespace std;

constexpr int N = 32, INF = 0x3f3f3f3f;
int n, m, s, deg, ans, g[N][N];
unordered_map<string, int> sh;

int c[N], t[N][N], ner[N], con[N], vis[N];
vector<int> ver;
void prim(int s)
{
    ner[s] = 0;
    for (size_t _ = 1; _ < ver.size(); _++)
    {
        int u = 0;
        for (int i : ver)
            if (!vis[i] && (!u || ner[i] < ner[u]))
                u = i;
        vis[u] = 1;
        for (int v : ver)
            if (!vis[v] && ner[v] > g[u][v])
                ner[v] = g[u][v], con[v] = u;
    }
    int p = s;
    for (int i : ver)
    {
        if (i == s)
            continue;
        ans += ner[i], t[con[i]][i] = t[i][con[i]] = ner[i];
        if (g[1][i] < g[1][p])
            p = i;
    }
    deg++, ans += g[1][p];
    t[1][p] = t[p][1] = g[1][p];
}
void color(int u)
{
    ver.emplace_back(u), c[u] = 1;
    for (int v = 1; v <= n; v++)
        if (g[u][v] != INF && !c[v])
            color(v);
}
int f[N], fu[N], fv[N]; // 记录 1 ~ i 路径上的最大边，边权是 f[i]
void prepare(int u)
{
    vis[u] = 1;
    for (int v = 1; v <= n; v++)
    {
        if (t[u][v] == INF || vis[v])
            continue;
        if (f[u] > t[u][v])
            f[v] = f[u], fu[v] = fu[u], fv[v] = fv[u];
        else
            f[v] = t[u][v], fu[v] = u, fv[v] = v;
        prepare(v);
    }
    vis[u] = 0;
}

bool trim()
{
    int mnv = INF, p = 0;
    for (int i = 2; i <= n; i++) // 枚举从 1 出发的非树边
    {
        if (g[1][i] == INF || t[1][i] != INF)
            continue;
        if (g[1][i] - t[fu[i]][fv[i]] < mnv)
            mnv = g[1][i] - t[fu[i]][fv[i]], p = i;
    }
    if (mnv >= 0)
        return false;
    ans += mnv, t[1][p] = t[p][1] = g[1][p], t[fu[p]][fv[p]] = t[fv[p]][fu[p]] = INF;

    // 重新计算以 p 为根的子树的 dp 状态
    f[p] = g[1][p], fu[p] = 1, fv[p] = p;
    vis[1] = true, prepare(p);
    return true;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m;
    sh["Park"] = 1, n = 1, memset(g, 0x3f, sizeof(g));
    for (int i = 1, u, v, w; i <= m; i++)
    {
        string p1, p2;
        cin >> p1 >> p2 >> w;
        !sh[p1] && (sh[p1] = ++n), !sh[p2] && (sh[p2] = ++n);
        u = sh[p1], v = sh[p2];
        g[u][v] = g[v][u] = min(g[u][v], w);
    }
    cin >> s;

    memset(t, 0x3f, sizeof(t)), memset(ner, 0x3f, sizeof(ner));
    c[1] = 1; // 删去 1 号点，每个连通块各自求 Prim
    for (int i = 2; i <= n; i++)
        if (!c[i])
            ver.clear(), color(i), prim(i);
    memset(vis, 0, sizeof(vis));
    prepare(1);

    while (deg < s && trim())
        deg++;
    cout << "Total miles driven: " << ans;
    return 0;
}