#include <bits/stdc++.h>
using namespace std;

const int MAX = 3e3 + 10;

struct edge
{
    int nxt, w;
};
vector<edge> graph[MAX];
int n, m, users[MAX], f[MAX][MAX];

void add(int u, int v, int w = 1)
{
    graph[u].push_back({v, w});
}
int dp(int u)
{
    if (u > n - m)
    {
        f[u][1] = users[u];
        return 1;
    }
    int sum = 0, son;
    for (auto i : graph[u])
    {
        int v = i.nxt;
        son = dp(v);
        sum += son;
        for (int j = sum; j > 0; j--)
            for (int k = 1; k <= son; k++)
                if (j - k >= 0)
                    f[u][j] = max(f[u][j], f[u][j - k] + f[v][k] - i.w);
    }
    return sum;
}

int main()
{
    memset(f, ~0x7f, sizeof(f));
    cin >> n >> m;
    int k, v, w;
    for (int u = 1; u <= n - m; u++)
    {
        cin >> k;
        while (k--)
            cin >> v >> w, add(u, v, w);
    }
    for (int i = n - m + 1; i <= n; i++)
        cin >> users[i];
    for (int i = 1; i <= n; i++)
        f[i][0] = 0;
    dp(1);
    for (int i = m; i >= 1; i--)
        if (f[1][i] >= 0)
        {
            cout << i;
            return 0;
        }
    return 0;
}
