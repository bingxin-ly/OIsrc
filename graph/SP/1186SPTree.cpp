#include <bits/stdc++.h>
using namespace std;

namespace segtr
{

}
constexpr int N = 1005;
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

using namespace segtr;
pair<int, int> P[N];
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
    memset(TD, 0x3f, sizeof(TD)), dijkstra(n, TD, TF), contact(T, TF);
    int p = n, idx = 0;
    while (p != 1)
        P[++idx] = {SF[p], p}, p = SF[p];
    reverse(P + 1, P + idx + 1), build(1, 1, idx);
    /* for (int i = 1; i <= idx; i++)
        cerr << P[i].first << ' ';
    cerr << P[idx].second << endl; */
    return 0;
}