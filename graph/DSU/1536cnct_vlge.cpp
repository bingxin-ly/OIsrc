#include <iostream>
#include "include/DSU.h"

int main()
{
begin:
    int n, m, ans = 0;
    cin >> n;
    if (!n)
        return 0;
    cin >> m;
    DSU s(n);
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        s.unite(u, v);
    }
    for (int i = 1; i <= n; i++)
    {
        if (s.find(i) == i)
            ans++;
    }
    cout << ans - 1 << endl;
    goto begin;
}