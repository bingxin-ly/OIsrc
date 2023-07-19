/* 四维线性 DP
   不变的信息：棋盘、手牌总数；变化的信息：棋子、用过的手牌
   题目中保证到达终点时刚好用光 M 张爬行卡片，且卡片与路径长度相关，
   考虑用卡片来表示状态，同时也可导出位置，避免重复记录。
   四种卡片四种步长，一步一步走，由上一步走来，也就是决策，阶段和转移
 */
#include <bits/stdc++.h>
using namespace std;

int n, m, s[355], c[5];
int f[41][41][41][41];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    for (int i = 1, x; i <= m; i++)
        cin >> x, c[x] += 1;
    memset(f, ~0x3f, sizeof(f)), f[0][0][0][0] = s[1];
    for (int i = 0; i <= c[4]; i++)
        for (int j = 0; j <= c[3]; j++)
            for (int k = 0; k <= c[2]; k++)
                for (int l = 0; l <= c[1]; l++)
                {
                    int d = i * 4 + j * 3 + k * 2 + l + 1;
                    if (i)
                        f[i][j][k][l] = max(f[i][j][k][l], f[i - 1][j][k][l] + s[d]);
                    if (j)
                        f[i][j][k][l] = max(f[i][j][k][l], f[i][j - 1][k][l] + s[d]);
                    if (k)
                        f[i][j][k][l] = max(f[i][j][k][l], f[i][j][k - 1][l] + s[d]);
                    if (l)
                        f[i][j][k][l] = max(f[i][j][k][l], f[i][j][k][l - 1] + s[d]);
                }
    cout << f[c[4]][c[3]][c[2]][c[1]];
    return 0;
}