/* 咕了好久的基础换根 DP
   换根 DP 就是在处理无根树上的 DP 时，先指定一个根，将这个无根树转化为有根树进行 DP，
   之后再计算新根和旧根之间的差，O(1) 换根，达到两边扫描求出以整棵树的任意节点为根时的答案
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int n, f[N], g[N];
vector<pair<int, int>> gh[N];

void dp(int u, int p)
{
    for (const auto &[v, c] : gh[u])
    {
        if (v == p)
            continue;
        dp(v, u);
        if (gh[v].size() == 1ll)
            f[u] += c;
        else
            f[u] += min(f[v], c);
    }
}
void dfs(int u, int p)
{
    for (const auto &[v, c] : gh[u])
    {
        if (v == p)
            continue;
        g[v] = f[v];
        if (gh[u].size() == 1ll)
            g[v] += c;
        else
            g[v] += min(g[u] - min(f[v], c), c);
        dfs(v, u);
    }
}
void solve()
{
    cin >> n;
    for (int i = 1, u, v, c; i < n; i++)
        cin >> u >> v >> c,
            gh[u].emplace_back(v, c), gh[v].emplace_back(u, c);
    dp(1, 0), g[1] = f[1], dfs(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, g[i]);
    cout << ans << '\n';
}
void clear()
{
    for (int i = 1; i <= n; i++)
        gh[i].clear();
    memset(f, 0, sizeof(f));
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve(), clear();
    return 0;
}