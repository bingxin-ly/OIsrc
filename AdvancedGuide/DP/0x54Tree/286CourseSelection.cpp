/* 有树形依赖关系的背包，被背包卡了好久 kk
   https://github.com/lydrainbowcat/tedukuri/blob/master/%E9%85%8D%E5%A5%97%E5%85%89%E7%9B%98/%E4%BE%8B%E9%A2%98/0x50%20%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/0x54%20%E6%A0%91%E5%BD%A2DP/%E9%80%89%E8%AF%BE/std.cpp
   节点的儿子是阶段，体积是状态，选几个是决策
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 309;
int n, m, s[N], f[N][N];
vector<int> tr[N];

void dp(int u)
{
    f[u][0] = 0;
    for (int v : tr[u])
    {
        dp(v);
        for (int j = m; j >= 0; j--)
            for (int k = 0; k <= j; k++)
                f[u][j] = max(f[u][j], f[u][j - k] + f[v][k]);
    }
    if (u != 0)
        for (int j = m; j; j--)
            f[u][j] = f[u][j - 1] + s[u];
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int u = 1, p; u <= n; u++)
        cin >> p >> s[u], tr[p].emplace_back(u);
    memset(f, ~0x3f, sizeof(f));
    dp(0);
    cout << f[0][m];
    return 0;
}