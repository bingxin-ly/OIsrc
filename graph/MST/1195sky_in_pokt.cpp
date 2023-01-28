#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};

typedef vector<Edge> edgeset;

struct DSU
{
    vector<int> fa;
    explicit DSU(int size) : fa(size + 1)
    {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x)
    {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
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

edgeset genMST(int n, int m, int k, edgeset &edges)
{
    DSU s(n);
    // Kruskal
    sort(edges.begin() + 1, edges.end());
    int cnt = 0;
    edgeset result;
    for (int i = 1; i <= m; i++)
        if (s.unite(edges[i].u, edges[i].v))
        {
            result.push_back(edges[i]), cnt++;
            if (cnt == n - k)
                return result;
        }
    return {};
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    edgeset edges(m + 1);
    for (int i = 1; i <= m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    edgeset out = genMST(n, edges.size() - 1, k, edges);
    if (out.empty())
    {
        cout << "No Answer";
    }
    else
    {
        long long ans = 0;
        for (auto i : out)
            ans += i.w;
        cout << ans << endl;
    }
    return 0;
}