#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 边的储存
struct Edge
{
    int u, v;    // 起点与终点
    long long w; // 边权（有时无）
    // 重载小于号
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};

// stands for vector<Edge>, remember to add 1
typedef vector<Edge> edgeset;

vector<bool> connected;

/**
 * @brief 已知端点找边函数
 * @param u,v two vertices
 * @param edges source edges
 * @return the edge corresponding, or null if not found
 */
Edge find_edge(int u, int v, edgeset &edges)
{
    int m = edges.size();
    for (int i = 1; i <= m; i++)
        if (edges[i].u == u && edges[i].v == v)
            return edges[i];
    return {};
}
void dfs(int u, edgeset &edges)
{
    if (connected[u])
        return;
    connected[u] = true;
    for (auto v : edges)
        if (v.u == u)
            dfs(v.v, edges);
}
#include <vector>
#include <numeric>
using namespace std;

/**
 * @brief Structure for managing DSU
 * @param size size of the DSU
 * @note 注意向量fa下标0与1的关系
 */
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
    // 非启发式合并
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
/**
 * @brief Structure for generating the MST
 * @param n number of vertices
 * @param edges set of edges
 * @note 注意向量fa下标0与1的关系
 */
struct MST
{
    int n, m, k;
    edgeset edges;

    MST(int n, edgeset &edges, int k = 1) : n(n), m(edges.size() - 1), edges(edges), k(k) {}

    /**
     *  @brief MST的生成，使用Kruskal算法
     *  @return number of the MSTs, 0 if not found
     */
    edgeset generate()
    {
        DSU s(n);
        // edges.resize(m + 1); // 是m！是m！
        // for (int i = 1; i <= m; i++)
        //     cin >> edges[i].u >> edges[i].v >> edges[i].w;

        // Kruskal
        sort(edges.begin() + 1, edges.end()); // 按边权排序
        int cnt = 0;
        edgeset result;
        for (int i = 1; i <= m; i++)
            if (s.unite(edges[i].u, edges[i].v))
                result.push_back(edges[i]), cnt++;
        if (cnt > n - k)
            return {};
        else
            return result;
    }
};

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    edgeset edges(m + 1);
    for (int i = 1; i <= m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    edgeset out = MST(n, edges, k).generate();
    if (out.empty())
    {
        cout << "No answer";
        return 0;
    }
    int ans = 0;
    for (auto i : edges)
        ans += i.w;
    cout << ans << endl;
}