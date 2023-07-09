/* 在本题中，要理解的一点便是：轮廓也可以作为状态。当我们假设从高到低安排每个人的位置的时候，题目中要求的高低次序
   其实已经满足，我们只需要考虑把人放在这的这个位置合不合法即可，这样，我们状态的表示就与之前已经站好的人无关，而
   一个 k元组（a1, a2, a3, ..., ak）描绘的轮廓内的合影方案总数就足以构成一个子问题。从而在人数上转移。
 */
#include <bits/stdc++.h>
using namespace std;

int k, ks[5];
long long f[31][31][31][31][31];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> k, k)
    {
        // memset(ks, 0, sizeof ks);
        for (int i = 0; i < k; i++)
            cin >> ks[i];
        while (k < 5)
            ks[k++] = 0; // 要设 0 啊，多测清空
        memset(f, 0, sizeof f), f[0][0][0][0][0] = 1;
        for (int a = 0; a <= ks[0]; a++)
            for (int b = 0; b <= ks[1]; b++)
                for (int c = 0; c <= ks[2]; c++)
                    for (int d = 0; d <= ks[3]; d++)
                        for (int e = 0; e <= ks[4]; e++)
                        {
                            if (a < ks[0])
                                f[a + 1][b][c][d][e] += f[a][b][c][d][e];
                            if (b < ks[1] && a > b)
                                f[a][b + 1][c][d][e] += f[a][b][c][d][e];
                            if (c < ks[2] && b > c)
                                f[a][b][c + 1][d][e] += f[a][b][c][d][e];
                            if (d < ks[3] && c > d)
                                f[a][b][c][d + 1][e] += f[a][b][c][d][e];
                            if (e < ks[4] && d > e)
                                f[a][b][c][d][e + 1] += f[a][b][c][d][e];
                        }
        cout << f[ks[0]][ks[1]][ks[2]][ks[3]][ks[4]] << '\n';
    }
    return 0;
}