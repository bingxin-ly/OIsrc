#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 10;
int dfn[N], low[N];
int src, dcnt;
vector<int> graph[N], cutnode;

inline void add(int u, int v)
{
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void tarjan(int cur)
{
    dfn[cur] = low[cur] = ++dcnt;
    int cnt = 0;
    for (auto to : graph[cur])
    {
        if (!dfn[to])
        {
            tarjan(to);
            low[cur] = min(low[cur], low[to]);
            if (low[to] >= dfn[cur])
                ++cnt;
        }
        else
            low[cur] = min(low[cur], dfn[to]);
    }
    if (cur == src && cnt >= 2)
        cutnode.push_back(cur);
    if (cur != src && cnt >= 1)
        cutnode.push_back(cur);
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, add(u, v);
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            src = i,
            tarjan(i);

    cout << cutnode.size() << endl;
    sort(cutnode.begin(), cutnode.end());
    for (auto i : cutnode)
        cout << i << ' ';
    return 0;
}
