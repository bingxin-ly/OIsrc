#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10, M = 6e5 + 10;
int idx, head[N];
pair<int, int> e[M << 1];
auto add = [](int u, int v)
{ e[++idx].first = v, e[idx].second = head[u], head[u] = idx; };

int match[N], vis[N];
bool find(int u)
{
    for (int i = head[u]; i; i = e[i].second)
    {
        int j = e[i].first;
        if (!vis[j])
        {
            vis[j] = true;
            if (!match[j] || find(match[j]))
            {
                match[j] = u;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, add(u, v);

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