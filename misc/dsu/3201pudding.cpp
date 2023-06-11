#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;
int src[N];
set<int> col[M];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m, tot = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> src[i], tot += src[i] != src[i - 1],
            col[src[i]].insert(i);

    while (m--)
    {
        int opt, x, y;
        cin >> opt;
        if (opt == 2)
            cout << tot << '\n';
        else
        {
            cin >> x >> y;
            if (x == y)
                continue;
            if (col[x].size() > col[y].size())
                col[x].swap(col[y]);
            for (int i : col[x])
                tot -= col[y].count(i - 1) + col[y].count(i + 1);
            for (int i : col[x])
                col[y].insert(i);
            col[x].clear();
        }
    }
    return 0;
}