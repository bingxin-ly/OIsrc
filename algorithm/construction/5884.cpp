#include <bits/stdc++.h>
using namespace std;

int n, deg[1501];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    int r = n * (n - 1) / 2, u, v;
    while (r--)
    {
        cin >> u >> v;
        if (u < v)
            swap(u, v);
        cout << (++deg[u] == u) << '\n';
    }
    return 0;
}