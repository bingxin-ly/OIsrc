#include <bits/stdc++.h>
using namespace std;

bool vis[1010];
int k, n, m, ans;
int mk[1010], a[1010];
vector<int> b[1010];

void dfs(int x)
{
    vis[x] = 1;
    mk[x]++;
    for (int i = 0; i < b[x].size(); i++)
        if (!vis[b[x][i]])
            dfs(b[x][i]);
}
int main()
{
    int x, y;
    cin >> k >> n >> m;
    for (int i = 1; i <= k; i++)
        cin >> a[i];
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        b[x].push_back(y);
    }
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= n; j++)
            vis[j] = 0;
        dfs(a[i]);
    }
    for (int i = 1; i <= n; i++)
        if (mk[i] == k)
            ans++;
    cout << ans;
    return 0;
}