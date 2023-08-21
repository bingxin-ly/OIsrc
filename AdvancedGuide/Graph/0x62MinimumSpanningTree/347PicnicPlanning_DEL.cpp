#include <bits/stdc++.h>
using namespace std;

constexpr int N = 32, INF = 0x3f3f3f3f;
int n, m, s, deg, ans, g[N][N], t[N][N];
void input()
{
    cin >> m;
    unordered_map<string, int> sh;
    sh["Park"] = 1, n = 1, memset(g, 0x3f, sizeof(g));
    string p1, p2;
    for (int i = 1, u, v, w; i <= m; i++)
    {
        cin >> p1 >> p2 >> w;
        !sh[p1] && (sh[p1] = ++n), !sh[p2] && (sh[p2] = ++n);
        u = sh[p1], v = sh[p2];
        g[u][v] = g[v][u] = min(g[u][v], w);
    }
    cin >> s;
}
int ner[N], vis[N], con[N];
void prim()
{
    memset(ner, 0x3f, sizeof(ner)), ner[1] = 0;
    for (int _ = 1; _ < n; _++)
    {
        int u = 0;
        for (int i = 1; i <= n; i++)
            if (!vis[i] && (!u || ner[i] < ner[u]))
                u = i;
        vis[u] = true;
        for (int v = 1; v <= n; v++)
            if (!vis[v] && ner[v] > g[u][v])
                ner[v] = g[u][v], con[v] = u;
    }
    memset(t, 0x3f, sizeof(t));
    for (int i = 2; i <= n; i++)
        ans += ner[i], deg += con[i] == 1,
            t[con[i]][i] = t[i][con[i]] = ner[i];
}
void color(int u)
{
    vis[u] = 1;
    for (int v = 1; v <= n; v++)
        if (t[u][v] != INF && !vis[v])
            color(v);
}
int find(int &u, int &v)
{
    int ret = INF;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            continue;
        for (int j = 2; j <= n; j++)
        {
            if (vis[j])
                continue;
            if (g[i][j] < ret)
                ret = g[i][j], u = i, v = j;
        }
    }
    return ret;
}
void trim()
{
    int mnv = INF, e = 0, x = 0, y = 0;
    for (int i = 2, u, v; i <= n; i++)
    {
        if (t[1][i] == INF)
            continue;
        memset(vis, 0, sizeof(vis)), vis[1] = 1, color(i);
        int res = find(u, v);
        if (res != INF && res - g[1][i] < mnv)
            mnv = res - g[1][i], e = i, x = u, y = v;
    }
    ans += mnv, t[1][e] = t[e][1] = INF, t[x][y] = t[y][x] = g[x][y];
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    input();
    prim();
    while (deg > s)
        trim(), deg--;
    cout << "Total miles driven: " << ans;
    return 0;
}