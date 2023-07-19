/* 变化的信息：之前把花（i）插哪（j）了
   转移：按“花”算：第 i + 1 朵花插第 k (k > j) 个花瓶
        按“瓶”算：第 j + 1 个花瓶 插不插？
   注意到，第 i 束花只能插在第 i - 1 束花之后的任意位置，
   所以状态在记录时还要多一个位置，方便转移
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int n, m, s[N][N], f[N][N], c[N][N];

void print(int i, int j)
{
    if (!i)
        return;
    print(i - 1, c[i][j]);
    cout << j << ' ';
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> s[i][j];
    memset(f, ~0x3f, sizeof(f)); // 美丽值有负数
    for (int j = 0; j <= m; j++)
        f[0][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= m; j++)
            for (int k = i - 1; k < j; k++)
                if (f[i][j] < f[i - 1][k] + s[i][j])
                    f[i][j] = f[i - 1][k] + s[i][j], c[i][j] = k;
    int ans = ~0x3f3f3f3f, tail = 0;
    for (int j = n; j <= m; j++)
        if (ans < f[n][j])
            ans = f[n][j], tail = j;
    cout << ans << '\n';
    print(n, tail);
    return 0;
}