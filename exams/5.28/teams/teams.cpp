#include <bits/stdc++.h>
using namespace std;

inline void chkmax(int &x, int y) { x = x > y ? x : y; }

int n, ans;
array<string, 3> name[20];
unordered_map<string, bool> mp;
void dfs(int now, int cnt)
{
    chkmax(ans, cnt);
    if (now == n + 1)
        return chkmax(ans, cnt);

    dfs(now + 1, cnt);
    for (auto i : name[now])
        if (mp[i])
            return;

    for (auto i : name[now])
        mp[i] = true;
    dfs(now + 1, cnt + 1);
    for (auto i : name[now])
        mp[i] = false;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 3; j++)
            cin >> name[i][j];
    dfs(1, 0);
    cout << ans;
    return 0;
}