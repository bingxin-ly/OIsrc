#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 10;
vector<bool> connected;

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &other) const { return w < other.w; }
};
typedef vector<Edge> edgeset;

struct DSU
{
    int fa[MAX];
    explicit DSU(int size)
    {
        // 重组预留的初始化
        for (int i = 0; i <= size; i++)
            fa[i] = i;
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

edgeset generate(int n, int m, edgeset graph)
{
    DSU s(n);
    sort(graph.begin(), graph.end());
    int cnt = 0;
    edgeset result;
    for (int i = 0; i < m; i++)
        if (s.unite(graph[i].u, graph[i].v))
            result.push_back(graph[i]), cnt++;
    if (cnt != n - 1)
        return {};
    else
        return result;
}

int main()
{
    int n, m;
    cin >> n >> m;
    edgeset graph(m);
    for (int i = 0; i < m; i++)
        cin >> graph[i].u >> graph[i].v >> graph[i].w;

    edgeset mintr = generate(n, m, graph);
    if (mintr.empty())
    {
        cout << "orz" << endl;
        return 0;
    }
    int ans = 0;
    for (auto i : mintr)
        ans += i.w;
    cout << ans << endl;
}