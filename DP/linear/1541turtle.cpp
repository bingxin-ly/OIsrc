/* **知道使用哪几张卡片后，我们就能推出现在到了哪一个位置**
   我们把状态表示变一变，f[i][a][b][c][d] 肯定是不好的，不满足原则
   改成 f[a][b][c][d] 即为用了这么多张卡片
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 355, C = 45;
int n, m, a[N], b[5], f[45][45][45][45];

inline void ckmax(int &x, int y) { (y > x) && (x = y); }
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1, x; i <= m; i++)
        cin >> x, b[x] += 1;
    // f[0][0][0][0] = a[1]; // 会重复，悲
    for (int b1 = 0; b1 <= b[1]; b1++)
        for (int b2 = 0; b2 <= b[2]; b2++)
            for (int b3 = 0; b3 <= b[3]; b3++)
                for (int b4 = 0; b4 <= b[4]; b4++)
                {
                    int p = 1 + b1 + b2 * 2 + b3 * 3 + b4 * 4;
                    if (b1)
                        ckmax(f[b1][b2][b3][b4], f[b1 - 1][b2][b3][b4]);
                    if (b2)
                        ckmax(f[b1][b2][b3][b4], f[b1][b2 - 1][b3][b4]);
                    if (b3)
                        ckmax(f[b1][b2][b3][b4], f[b1][b2][b3 - 1][b4]);
                    if (b4)
                        ckmax(f[b1][b2][b3][b4], f[b1][b2][b3][b4 - 1]);
                    f[b1][b2][b3][b4] += a[p];
                }
    cout << f[b[1]][b[2]][b[3]][b[4]];
    return 0;
}