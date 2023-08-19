#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e3 + 5, M = 2e5 + 5;
int n, m;
namespace Kruskal
{
    struct E
    {
        int u, v, w;
    } edgs[M];
    bool operator<(const E &x, const E &y) { return x.w < y.w; }

    int p[N];
    int find(int x) { return x == p[x] ? x : find(p[x]); }

    int kruskal()
    {
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
            cin >> edgs[i].u >> edgs[i].v >> edgs[i].w;
        sort(edgs + 1, edgs + m + 1), iota(p + 1, p + n + 1, 1);
        int sum = 0, cnt = 0;
        for (int i = 1; i <= m; i++)
        {
            int x = find(edgs[i].u), y = find(edgs[i].v);
            if (x == y)
                continue;
            cnt += 1, sum += edgs[i].w, p[x] = y;
        }
        return n != n - 1 ? -1 : sum;
    }
}
namespace Prim
{
    int w[N][N], ner[N], vis[N];
    int prim()
    {
        cin >> n >> m;
        memset(w, 0x3f, sizeof(w));
        for (int i = 1, u, v, w_; i <= m; i++)
            cin >> u >> v >> w_, w[u][v] = w[v][u] = min(w[u][v], w_);
        memset(ner, 0x3f, sizeof(ner)), memset(vis, 0, sizeof(vis));
        ner[1] = 0; // 一开始 T 中只有 1
        for (int _ = 1; _ < n; _++)
        {
            int mn = 0;
            for (int u = 1; u <= n; u++)
                if (!vis[u] && (!u || ner[u] < ner[mn]))
                    mn = u;
            if (ner[mn] > 1e4)
                cout << "orz", exit(0);
            vis[mn] = 1;
            for (int v = 1; v <= n; v++)
                if (!vis[v])
                    ner[v] = min(ner[v], w[mn][v]);
        }
        return accumulate(ner + 2, ner + n + 1, 0);
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cout << "This is the MST\n";
    return 0;
}