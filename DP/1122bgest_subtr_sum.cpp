#include <bits/stdc++.h>
using namespace std;

const int N = 16e3 + 10;
int n, a[N], f[N], ans = INT_MIN;
vector<int> E[N];

void dfs(int u, int fa)
{
    f[u] = a[u];
    for (int i = 0; i < E[u].size(); i++)
    {
        int t = E[u][i];
        if (t != fa)
        {
            dfs(t, u);
            if (f[t] > 0)
                f[u] += f[t];
        }
    }
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i]);
    cout << ans;
    return 0;
}