#include <bits/stdc++.h>
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

int main()
{
    int n, m;
    cin >> n >> m;
    DSU u(n);
    for (int i = 1, z, x, y; i <= m; i++)
    {
        cin >> z >> x >> y;
        if (z == 1)
            u.unite(x, y);
        else
            cout << (u.find(x) == u.find(y) ? "Y" : "N") << endl;
    }
    return 0;
}
