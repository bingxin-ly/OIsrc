#include <iostream>
#include "include/MST.h"

int main()
{
    int n, m;
    cin >> n >> m;
    edgeset edges(m + 1);
    for (int i = 1; i <= m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    MST mst(n, edges);
    edgeset out = mst.generate();
    int ans = 0;
    for (auto i : out)
        ans += i.w;
    cout << ans << endl;
}