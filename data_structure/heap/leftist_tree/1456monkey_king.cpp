#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int fa[N], ls[N], rs[N], heap[N], dist[N]{-1};
int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int merge(int x, int y)
{
    if (!x || !y)
        return x | y;

    if (heap[x] < heap[y]) // 大根堆！！
        swap(x, y);
    rs[x] = merge(rs[x], y);
    if (dist[ls[x]] < dist[rs[x]])
        swap(ls[x], rs[x]);
    fa[ls[x]] = fa[rs[x]] = fa[x] = x;
    dist[x] = dist[rs[x]] + 1;
    return x;
}
int weak(int x)
{
    heap[x] >>= 1;
    int rt = merge(ls[x], rs[x]);
    ls[x] = rs[x] = dist[x] = 0;
    return fa[rt] = fa[x] = merge(rt, x);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    while (cin >> n)
    {
        dist[0] = -1;
        for (int i = 1; i <= n; i++)
            ls[i] = rs[i] = dist[i] = 0, fa[i] = i,
            cin >> heap[i];
        cin >> m;
        for (int i = 1, x, y; i <= m; i++)
        {
            cin >> x >> y;
            x = find(x), y = find(y);
            if (x == y)
                cout << "-1\n";
            else
            {
                int l = weak(x), r = weak(y);
                fa[l] = fa[r] = merge(l, r);
                cout << heap[fa[l]] << '\n';
            }
        }
    }
    return 0;
}