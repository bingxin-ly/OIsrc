#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
vector<int> graph[N];

int n, m;
ssize_t size[N], ans[N];

int dcnt, dfn[N], low[N];
int cut[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++dcnt;
    size[u] = 1;
    int flag = 0, sum = 0;
    for (auto v : graph[u])
    {
        if (!dfn[v])
        {
            tarjan(v);
            size[u] += size[v];
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])
            {
                ans[u] += (ssize_t)size[v] * (n - size[v]);
                sum += size[v];
                flag++;
                if (u != 1 || flag > 1)
                    cut[u] = true;
            }
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
    if (!cut[u])
        ans[u] = 2 * (n - 1);
    else
        ans[u] += (ssize_t)(n - sum - 1) * (sum + 1) + (n - 1);
}

int main()
{
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    tarjan(1);

    for (int i = 1; i <= n; i++)
        cout << ans[i] << endl;
    return 0;
}