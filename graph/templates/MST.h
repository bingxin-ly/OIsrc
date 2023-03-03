#include <algorithm>
#include "Edge.h"
#include "DSU.h"

/**
 * @brief Structure for generating the MST
 * @param n number of vertices
 * @param edges set of edges
 * @note 注意向量fa下标0与1的关系
 */
/* struct MST
{
    int n, m;
    edgeset edges;

    MST(int n, edgeset &edges) : n(n), m(edges.size() - 1), edges(edges) {}
 */
    /**
     *  @brief MST的生成
     *  @return number of the MSTs, 0 if not found
     */
    edgeset generate(int n, int m, edgeset graph)
    {
        DSU s(n);
        // edges.resize(m + 1); // 是m！是m！
        // for (int i = 1; i <= m; i++)
        //     cin >> edges[i].u >> edges[i].v >> edges[i].w;

        // Kruskal
        sort(edges.begin(), edges.end()); // 按边权排序
        int cnt = 0;
        edgeset result;
        for (int i = 0; i < m; i++)
            if (s.unite(edges[i].u, edges[i].v))
                result.push_back(edges[i]), cnt++;
        if (cnt != n - 1)
            return {};
        else
            return result;
    }
// };
