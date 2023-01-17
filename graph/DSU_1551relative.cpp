#include <iostream>
#include "include/DSU.h"

int main()
{
    ios_base::sync_with_stdio(false);// 快读
    int n, m, p;
    cin >> n >> m >> p;
    DSU s(n);
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, s.unite(u, v);
    for (int i = 1, u, v; i <= p; i++)
    {
        cin >> u >> v;
        cout << (s.find(u) != s.find(v) ? "No" : "Yes") << endl;
    }
}