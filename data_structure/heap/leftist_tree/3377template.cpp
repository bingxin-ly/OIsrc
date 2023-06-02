#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
bool del[N];
int heap[N], dist[N], fa[N], ls[N], rs[N];
int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int merge(int x, int y)
{
    if (!x || !y)
        return x | y;

    if (heap[x] == heap[y] ? x > y : heap[x] > heap[y])
        swap(x, y);
    rs[x] = merge(rs[x], y);
    if (dist[ls[x]] < dist[rs[x]])
        swap(ls[x], rs[x]);
    fa[ls[x]] = fa[rs[x]] = fa[x] = x;
    dist[x] = dist[rs[x]] + 1;
    return x;
}
void pop(int x)
{
    del[x] = true;
    fa[ls[x]] = ls[x], fa[rs[x]] = rs[x];
    fa[x] = merge(ls[x], rs[x]);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    dist[0] = -1;
    for (int i = 1; i <= n; i++)
        fa[i] = i;

    for (int i = 1; i <= n; i++)
        cin >> heap[i];
    for (int i = 1, x, y, opt; i <= m; i++)
    {
        cin >> opt;
        if (opt == 1)
        {
            cin >> x >> y;
            if (del[x] || del[y])
                continue;
            x = find(x), y = find(y);
            if (x != y)
                fa[x] = fa[y] = merge(x, y);
        }
        else
        {
            cin >> x;
            if (del[x])
            {
                cout << "-1\n";
                continue;
            }
            x = find(x);
            cout << heap[x] << '\n';
            pop(x);
        }
    }
    return 0;
}