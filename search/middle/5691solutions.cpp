#include <bits/stdc++.h>
using namespace std;

int n, m, k[7], p[7], ans;
unordered_map<int, int> mp;

void dfs1(int dep, int val)
{
    if (dep > (n >> 1))
        return mp[val]++, void();
    for (int i = 1; i <= m; i++)
        dfs1(dep + 1, val + k[dep] * pow(i, p[dep]));
}
void dfs2(int dep, int val)
{
    if (dep > n)
        return ans += mp[val], void();
    for (int i = 1; i <= m; i++)
        dfs2(dep + 1, val - k[dep] * pow(i, p[dep]));
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> k[i] >> p[i];
    dfs1(1, 0), dfs2((n >> 1) + 1, 0);
    cout << ans;
    return 0;
}
