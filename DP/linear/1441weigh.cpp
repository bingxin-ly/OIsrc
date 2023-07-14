#include <bits/stdc++.h>
using namespace std;

int n, m, w[25], ans;
bool f[2005];

vector<int> cho;
void dfs(int x)
{
    if (cho.size() > (size_t)m || cho.size() + (n - x + 1) < (size_t)m)
        return;
    if (x == n + 1)
    {
        memset(f, 0, sizeof f);
        f[0] = 1;
        for (int i : cho)
            for (int j = 2000; j >= w[i]; j--)
                f[j] |= f[j - w[i]];
        int res = 0;
        for (int i = 1; i <= 2000; i++)
            res += f[i];
        ans = max(ans, res);
        return;
    }
    cho.emplace_back(x), dfs(x + 1), cho.pop_back();
    dfs(x + 1);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    m = n - m;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    dfs(1);
    cout << ans;
    return 0;
}