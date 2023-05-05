#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
int t, dep[N], f[N][20];

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

int seq[N], diff[N], ans[N];
void dfs(int u, int fa)
{
    for (auto v : graph[u])
        if (v != fa)
        {
            dfs(v, u);
            diff[u] += diff[v];
        }
}

int main()
{
    int n;
    cin >> n;
    t = int(log(n) / log(2)) + 1;
    for (int i = 1; i <= n; i++)
        cin >> seq[i];

    for (int i = 1, x, y; i < n; i++)
    {
        cin >> x >> y;
        add(x, y), add(y, x);
    }

    bfs(1);
    ans[seq[1]]++;
    for (int i = 2; i <= n; i++)
    {
        int u = seq[i - 1], v = seq[i];
        int top = lca(u, v);
        diff[u]++, diff[v]++, diff[top]--, diff[f[top][0]]--;
        ans[u]--;
    }
    ans[seq[n]]--;
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        cout << ans[i] + diff[i] << endl;
    return 0;
}
