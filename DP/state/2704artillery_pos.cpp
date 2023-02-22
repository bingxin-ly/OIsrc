#include <bits/stdc++.h>
#define chkmax(a, b) a = max(a, b)
using namespace std;

int n, m, cnt;
int terr[105], f[105][70][70], ones[1 << 10], mp[1 << 10];

int main()
{
    cin >> n >> m;
    char c;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> c, terr[i] <<= 1, terr[i] += (c == 'H');

    /* 2.判断每个状态有没有两个炮兵左右距离在两格之内:
    这个需要动脑想一下，我们发现一个神奇的结论，
    如果把表示当前状态的二进制数位运算左移一位，
    那么用这个结果与原状态做一次位运算与操作，如果结果不是 0，
    那么就一定存在两个炮兵左右距离在一格之内。
    同理，左移两位就可以判断左右距离在两格之内。
    这个过程也就是 S&(S<<1)，S&(S<<2)。 */
    for (int i = 0; i < 1 << m; i++)
    {
        if (i & i << 1 || i & i << 2)
            continue; // 不合法跳过
        /* 离散化
           枚举得出所有合法的位置，
           在dp时只根据离散后的数据转移即可
         */
        mp[cnt] = i;

        int cnt1 = 0;
        for (int j = 0; j < m; j++)
            if (i >> j & 1)
                cnt1++;
        ones[cnt] = cnt1; // 记录贡献

        cnt += 1;
    }

    // 初始化第一二排
    for (int j = 0; j < cnt; j++)
        if (!(mp[j] & terr[1]))
            f[1][j][0] = ones[j];

    for (int j = 0; j < cnt; j++)
        if (!(mp[j] & terr[2]))
            for (int k = 0; k < cnt; k++)
                if (!(mp[j] & mp[k] || mp[k] & terr[1]))
                    f[2][j][k] = ones[j] + ones[k];

    for (int i = 3; i <= n; i++)
        for (int j = 0; j < cnt; j++)
            if (!(mp[j] & terr[i]))
                for (int k = 0; k < cnt; k++)
                    if (!(mp[j] & mp[k] || mp[k] & terr[i - 1]))
                        for (int l = 0; l < cnt; l++)
                            if (!(mp[j] & mp[l] || mp[k] & mp[l] || mp[l] & terr[i - 2]))
                                chkmax(f[i][j][k], f[i - 1][k][l] + ones[j]);

    int ans = 0;
    for (int j = 0; j <= cnt; j++)
        for (int k = 0; k <= cnt; k++)
            chkmax(ans, f[n][j][k]);
    cout << ans << endl;
    return 0;
}