#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105, M = 10005;
namespace normal // 循规蹈矩版
{
    int w[N], f[N][M];
    signed main()
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> w[i];

        for (int i = 0; i <= n; i++)
            f[i][0] = 1; // 注意每个阶段都可以由什么都不选导出
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                f[i][j] += f[i - 1][j];
            for (int j = w[i]; j <= m; j++)
                f[i][j] += f[i - 1][j - w[i]];
        }
        cout << f[n][m];
        return 0;
    }
}
namespace roll // 滚动数组版
{
    int w[N], f[M];
    signed main()
    {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> w[i];

        f[0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = m; j >= w[i]; j--)
                f[j] += f[j - w[i]];
        cout << f[m];
        return 0;
    }
}
signed main() { return roll::main(); }