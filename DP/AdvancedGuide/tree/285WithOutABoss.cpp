/* 树形 DP 模版题
   今天听的 lyd 大佬的课，总结几点树形 DP 的思路
   树形 DP 和区间 DP 很像，区间 DP 对区间的枚举也构成了一棵树，
   其中每个大区间都是由小区间扩展而来的，区间长度便是他的阶段。
   而树形 DP 中则以深度（也即子树大小）为阶段，
   每个大子树（节点）都是由下面的子树得来的。
   在实现时通常采用递归的方式，先递归每个节点，回溯时进行状态转移
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 6005;
int n, h[N], v[N], f[N][2];
vector<int> tr[N];

// 树的结构很适合递归解决
void dp(int u)
{
    f[u][1] = h[u];
    for (int v : tr[u])
    {
        dp(v);
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    for (int i = 1, l, k; i < n; i++)
        cin >> l >> k, tr[k].emplace_back(l), v[l] = true;
    int rt = 1;
    while (v[rt])
        rt += 1;
    dp(rt);
    cout << max(f[rt][0], f[rt][1]);
    return 0;
}