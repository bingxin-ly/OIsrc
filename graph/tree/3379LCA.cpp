#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
int n, q, rt, t;
int f[N][20], dep[N];

vector<int> graph[N];
inline void add(int u, int v)
{
    graph[u].push_back(v);
}
void bfs(int u)
{
    queue<int> qu;
    dep[u] = 1;
    qu.push(u);
    while (!qu.empty())
    {
        int x = qu.front();
        qu.pop();
        for (auto i : graph[x])
        {
            if (dep[i])
                continue;
            dep[i] = dep[x] + 1;
            f[i][0] = x;
            for (int j = 1; j <= t; j++)
                f[i][j] = f[f[i][j - 1]][j - 1];
            qu.push(i);
        }
    }
}
int lca(int x, int y)
{
    if (dep[x] > dep[y])
        swap(x, y);
    for (int i = t; i >= 0; i--)
        if (dep[f[y][i]] >= dep[x])
            y = f[y][i];
    if (x == y)
        return x;
    for (int i = t; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> q >> rt;
    t = int(log(n) / log(2)) + 1;
    for (int i = 1, x, y; i < n; i++)
    {
        cin >> x >> y;
        add(x, y), add(y, x);
    }
    bfs(rt); // pre
    int x, y;
    while (q--)
    {
        cin >> x >> y;
        cout << lca(x, y) << endl;
    }
    return 0;
}
