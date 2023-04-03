#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 10, M = 2e5 + 10;
struct edge
{
    int u, v, w;
    bool operator<(const edge &other) const { return w < other.w; }
};
typedef vector<edge> edgeset;

struct DSU
{
    int fa[N];
    explicit DSU(int size)
    {
        // 重组预留的初始化
        iota(fa, fa + size + 1, 0);
    }
    int find(int x)
    {
        // 注意找的是 fa!
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    bool unite(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return false;
        else
        {
            fa[x] = y;
            return true;
        }
    }
};

vector<int> genMST(int n, int m, edgeset &edges)
{
    DSU s(n);
    vector<int> res;

    sort(edges.begin(), edges.end());
    for (int i = 0; i < m; i++)
        if (s.unite(edges[i].u, edges[i].v))
            res.push_back(i);
    return res;
}

int main()
{
    int n, m;
    cin >> n >> m;
    edgeset graph(m);
    for (int i = 0; i < m; i++)
        cin >> graph[i].u >> graph[i].v >> graph[i].w;

    auto MST = genMST(n, m, graph);
    if (MST.size() != n - 1)
        return cout << "orz", 0;

    int ans = 0;
    for (auto i : MST)
        ans += graph[i].w;
    cout << ans;
    return 0;
}