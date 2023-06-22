// 蓝书上是变成全 0 矩阵，AW上的题是全亮着，好不坑我！
#include <bits/stdc++.h>
using namespace std;

bool sav[6][6], lit[6][6];
int ans, dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
void click(int x, int y)
{
    ans += 1, lit[x][y] ^= 1;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || nx > 5 || ny < 1 || ny > 5)
            continue;
        lit[nx][ny] ^= 1;
    }
}
int calc()
{
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 5; j++)
            if (!lit[i][j])
            {
                click(i + 1, j);
                if (ans > 6)
                    return 0x3f3f3f3f;
            }
    for (int j = 1; j <= 5; j++)
        if (!lit[5][j])
            return 0x3f3f3f3f;
    return ans;
}
int solve()
{
    for (int i = 1, ch = 0; i <= 5; i++)
        for (int j = 1; j <= 5; j++)
        {
            while (ch < '0' || ch > '1')
                ch = getchar();
            sav[i][j] = ch - '0', ch = getchar();
        }

    int ret = 0x3f3f3f3f;
    for (int i = 0; i < 1 << 5; i++)
    {
        ans = 0, memcpy(lit, sav, sizeof sav); // 简单类型
        for (int j = 0; j < 5; j++)
            if (i >> j & 1)
                click(1, j + 1);

        ret = min(ret, calc());
    }
    return ret != 0x3f3f3f3f ? ret : -1;
}
signed main()
{
    int n;
    scanf("%d", &n);
    while (n--)
        printf("%d\n", solve());
    return 0;
}