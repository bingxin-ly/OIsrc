/* 可以看出，这道题的动归范围在一个环上，且状态之间的转移只与前一阶段有关
   我们把它转化成线性问题以后，差别就在于 1 与 n 断开，无法进行状态的转移
   所以我们就可以在断开的位置补救一下，因为只有睡不和睡两种情况，1 不睡和睡各推一个
   调整初值和目标最终取一个最大值作为答案就好
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 4000;
int n, m, u[N], f[N][2];

void dp()
{
    for (int i = 2; i <= n; i++)
        for (int j = i; j >= 0; j--)
        {
            f[j][0] = max(f[j][0], f[j][1]);
            if (j > 0)
                f[j][1] = max(f[j - 1][0], f[j - 1][1] + u[i]);
        }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> u[i];
    memset(f, ~0x3f, sizeof(f)), f[0][0] = 0, f[1][1] = 0, dp();
    int ans1 = max(f[m][0], f[m][1]);
    memset(f, ~0x3f, sizeof(f)), f[1][1] = u[1], dp();
    int ans2 = f[m][1];
    cout << max(ans1, ans2);
    return 0;
}