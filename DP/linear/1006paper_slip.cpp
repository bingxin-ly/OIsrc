#include <bits/stdc++.h>
using namespace std;

constexpr int N = 55;
namespace quadra
{
#define max(a, b, c, d) max(max(a, b), max(c, d))
    int f[N][N][N][N], a[N][N];

    int main()
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> a[i][j];

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                for (int k = 1; k <= n; k++)
                    for (int l = 1; l <= m; l++)
                    {
                        f[i][j][k][l] =
                            max(f[i - 1][j][k - 1][l],
                                f[i - 1][j][k][l - 1],
                                f[i][j - 1][k - 1][l],
                                f[i][j - 1][k][l - 1]) +
                            a[i][j] + a[k][l];
                        if (i == k && l == j)
                            f[i][j][k][l] -= a[i][j];
                    }

        cout << f[n][m - 1][n - 1][m] << endl;
        return 0;
    }
}
namespace tri
{
    /* 如果我们把两条路径分开来处理，转移很清晰，但该如何判断是否重复经过一个位置呢？
       这就和路径有关系了，而我们的动归只允许从之前很简单的状态转移而来，存一个路径未免要求太高，
       这不是一个好的简化状态。我们思考，这两个点都是走的曼哈顿距离，两个点在同一个位置，
       它们走过的距离就必然是相同的。于是我们考虑让走的距离作为阶段，每次转移都让这两个点一起动，
       这样，由于路径固定，记录 x1, x2 即可，x1 + y1 = x2 + y2 = i + 2，
       在判断时 x1 == x2 即为重合。O(n^3)
     */
    int f[N << 1][N][N], a[N][N];
    inline void ckmax(int &x, int y) { (y > x) && (x = y); }
    signed main()
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> a[i][j];
        f[0][1][1] = a[1][1];
        for (int i = 0; i < n + m - 2; i++)
            for (int x1 = 1; x1 <= min(n, i + 1); x1++)
                for (int x2 = 1; x2 <= min(n, i + 1); x2++)
                {
                    int y1 = i + 2 - x1, y2 = i + 2 - x2;
                    ckmax(f[i + 1][x1][x2], f[i][x1][x2] + a[x1][y1 + 1] + (x1 != x2) * a[x2][y2 + 1]);         // 同时向下走
                    ckmax(f[i + 1][x1 + 1][x2 + 1], f[i][x1][x2] + a[x1 + 1][y1] + (x1 != x2) * a[x2 + 1][y2]); // 同时向右走

                    ckmax(f[i + 1][x1 + 1][x2], f[i][x1][x2] + a[x1 + 1][y1] + (x1 + 1 != x2) * a[x2][y2 + 1]);
                    ckmax(f[i + 1][x1][x2 + 1], f[i][x1][x2] + a[x1][y1 + 1] + (x2 + 1 != x1) * a[x2 + 1][y2]);
                }
        cout << f[n + m - 2][n][n]; // 横坐标
        return 0;
    }
}
signed main() { return tri::main(); }