/* 按照蓝书讲法的代码
   太ex了，没有别的，就是ex，做完觉得什么数据结构都是香的
 */
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

constexpr int N = 20;
int a[N][N], f[N][N * N][N][N][2][2];
signed char cl[N][N * N][N][N][2][2], cr[N][N * N][N][N][2][2], dx[N][N * N][N][N][2][2], dy[N][N * N][N][N][2][2];

int c, i, j, l, r, x, y;
void upd(int v, int L, int R, bool X, bool Y)
{
    if (f[i][j][l][r][x][y] > v)
        return;
    f[i][j][l][r][x][y] = v;
    cl[i][j][l][r][x][y] = L, cr[i][j][l][r][x][y] = R;
    dx[i][j][l][r][x][y] = X, dy[i][j][l][r][x][y] = Y;
}

void print(int i, int j, int l, int r, int x, int y)
{
    if (!j)
        return;
    print(i - 1, j - (r - l + 1), cl[i][j][l][r][x][y], cr[i][j][l][r][x][y], dx[i][j][l][r][x][y], dy[i][j][l][r][x][y]);
    for (j = l; j <= r; j++)
        cout << i << ' ' << j << '\n';
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            cin >> a[i][j], a[i][j] += a[i][j - 1];

    memset(f, ~0x3f, sizeof f);
    for (i = 0; i <= n; i++)
        f[i][0][0][0][1][0] = 0;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= k; j++)
            for (l = 1; l <= m; l++)
                for (r = l; r <= m; r++)
                {
                    if ((c = r - l + 1) > j) // 不合法的状态
                        break;
                    int s = a[i][r] - a[i][l - 1];
                    x = 1, y = 0;
                    if (c == j)
                        f[i][j][l][r][x][y] = f[i - 1][0][0][0][1][0] + s,
                        dx[i][j][l][r][x][y] = 1, dy[i][j][l][r][x][y] = 0;
                    else
                        for (int p = l; p <= r; p++)
                            for (int q = p; q <= r; q++)
                                upd(f[i - 1][j - c][p][q][1][0] + s, p, q, 1, 0);
                    x = 1, y = 1;
                    for (int p = l; p <= r; p++)
                        for (int q = r; q <= m; q++)
                            upd(f[i - 1][j - c][p][q][1][0] + s, p, q, 1, 0),
                                upd(f[i - 1][j - c][p][q][1][1] + s, p, q, 1, 1);
                    x = 0, y = 0;
                    for (int p = 1; p <= l; p++)
                        for (int q = l; q <= r; q++)
                            upd(f[i - 1][j - c][p][q][0][0] + s, p, q, 0, 0),
                                upd(f[i - 1][j - c][p][q][1][0] + s, p, q, 1, 0);
                    x = 0, y = 1;
                    for (int p = 1; p <= l; p++)
                        for (int q = r; q <= m; q++)
                            upd(f[i - 1][j - c][p][q][0][0] + s, p, q, 0, 0),
                                upd(f[i - 1][j - c][p][q][0][1] + s, p, q, 0, 1),
                                upd(f[i - 1][j - c][p][q][1][0] + s, p, q, 1, 0),
                                upd(f[i - 1][j - c][p][q][1][1] + s, p, q, 1, 1);
                }

    int ans = 0,
        ti, tl, tr, tx, ty;
    ti = tl = tr = tx = ty = 0;
    for (i = 1; i <= n; i++)
        for (l = 1; l <= m; l++)
            for (r = l; r <= m; r++)
                for (x = 0; x <= 1; x++)
                    for (y = 0; y <= 1; y++)
                        if (f[i][k][l][r][x][y] > ans)
                            ans = f[i][k][l][r][x][y],
                            ti = i, tl = l, tr = r, tx = x, ty = y;
    cout << "Oil : " << ans << '\n';
    print(ti, k, tl, tr, tx, ty);
    return 0;
}