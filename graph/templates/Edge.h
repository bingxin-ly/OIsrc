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