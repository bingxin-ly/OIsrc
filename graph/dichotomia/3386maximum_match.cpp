#include <bits/stdc++.h>
using namespace std;

const int N = 2 * 5e2 + 10;
vector<int> graph[N];

bool vis[N];
int match[N];
bool find(int u)
{
    for (auto i : graph[u])
        if (!vis[i])
        {
            vis[i] = true;
            if (!match[i] || find(match[i]))
                return match[i] = u, true;
        }
    return false;
}
int main()
{
    int n, m, e;
    cin >> n >> m >> e;
    for (int i = 1, u, v; i <= e; i++)
    {
        cin >> u >> v;
        v += n;
        graph[u].push_back(v);
    }

    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        memset(vis, false, sizeof(vis));
        if (find(i))
            res++;
    }
    cout << res;
    return 0;
}