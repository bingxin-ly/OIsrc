#include <bits/stdc++.h>
using namespace std;

int n, ord[20], vis[20];
void dfs(int x)
{
    if (x == n + 1)
    {
        for (int i = 1; i <= n; i++)
            cout << ord[i] << ' ';
        cout << '\n';
        return;
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i])
        {
            ord[x] = i, vis[i] = true, dfs(x + 1);
            vis[i] = false;
        }
}
signed main()
{
    cin >> n;
    dfs(1);
    return 0;
}