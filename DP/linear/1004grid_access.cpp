#include <bits/stdc++.h>
#define max(a, b, c, d) max(max(a, b), max(c, d))
using namespace std;

const int N = 10;
int f[N][N][N][N], src[N][N];

int main()
{
    int n, x, y, w;
    cin >> n;
    while (cin >> x >> y >> w)
        src[x][y] = w;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                for (int l = 1; l <= n; l++)
                {
                    f[i][j][k][l] = max(f[i - 1][j][k - 1][l],
                                        f[i - 1][j][k][l - 1],
                                        f[i][j - 1][k - 1][l],
                                        f[i][j - 1][k][l - 1]) +
                                    src[i][j] + src[k][l];
                    if (i == k && l == j)
                        f[i][j][k][l] -= src[i][j];
                }

    cout << f[n][n][n][n] << endl;
    return 0;
}

#undef max
// 深搜
#include <iostream>
using namespace std;

int N, s[15][15], f[11][11][11][11];
int dfs(int x, int y, int x2, int y2)
// 两种方案同时执行，表示当第一种方案走到x,y,第二种方案走到x2,y2时到终点取得的最大数
{
    if (f[x][y][x2][y2] != -1)
        return f[x][y][x2][y2]; // 如果这种情况已经被记录过了，直接返回，节省时间
    if (x == N && y == N && x2 == N && y2 == N)
        return 0; // 如果两种方案都走到了终点，返回结束
    int M = 0;
    // 如果两种方案都不在最后一列，就都往下走，统计取得的数，如果有重复，就减去一部分
    if (x < N && x2 < N)
        M = max(M, dfs(x + 1, y, x2 + 1, y2) + s[x + 1][y] + s[x2 + 1][y2] - s[x + 1][y] * (x + 1 == x2 + 1 && y == y2));

    // 如果第一种方案不在最后一行，第二种方案不在最后一列，第一种就向下走，第二种就向右走，
    // 统计取得的数，如果有重复，就减去一部分
    if (x < N && y2 < N)
        M = max(M, dfs(x + 1, y, x2, y2 + 1) + s[x + 1][y] + s[x2][y2 + 1] - s[x + 1][y] * (x + 1 == x2 && y == y2 + 1));

    // 如果第一种方案不在最后一列，第二种方案不在最后一行，第一种就向右走，第二种就向下走，
    // 统计取得的数，如果有重复，就减去一部分
    if (y < N && x2 < N)
        M = max(M, dfs(x, y + 1, x2 + 1, y2) + s[x][y + 1] + s[x2 + 1][y2] - s[x][y + 1] * (x == x2 + 1 && y + 1 == y2));

    // 如果第一种方案和第二种方案都不在最后一列，就都向右走
    // 统计取得的数，如果有重复，就减去一部分
    if (y < N && y2 < N)
        M = max(M, dfs(x, y + 1, x2, y2 + 1) + s[x][y + 1] + s[x2][y2 + 1] - s[x][y + 1] * (x == x2 && y + 1 == y2 + 1));

    // 对最后那个 s[x][y+1]*(x==x2&&y+1==y2+1))的解释：这个是用来判断两种方案是不是走到了同一格的
    // 如果是真，就返回1，否则返回0，如果是1的话，理所当然的可以减去s[x][y+1]*1,否则减去s[x][y+1]*0
    // 相当于不减,写得有点精简，省了4个if，见谅哈~
    f[x][y][x2][y2] = M; // 记录这种情况
    return M;            // 返回最大值
}
int main()
{
    cin >> N;
    // 将记录数组初始化成-1，因为可能出现取的数为0的情况，如果直接判断f[x][y][x2][y2]!=0（见dfs第一行）
    // 可能出现死循环而导致超时，细节问题
    for (int a = 0; a <= N; a++)
        for (int b = 0; b <= N; b++)
            for (int c = 0; c <= N; c++)
                for (int d = 0; d <= N; d++)
                    f[a][b][c][d] = -1;
    memset(f, -1, sizeof(f));
    while (true)
    // for (;;) // 读入
    {
        int t1 = 0, t2 = 0, t3 = 0;
        cin >> t1 >> t2 >> t3;
        if (t1 == 0 && t2 == 0 && t3 == 0)
            break;
        s[t1][t2] = t3;
    }
    cout << dfs(1, 1, 1, 1) + s[1][1]; // 输出，因为dfs中没有考虑第一格，即s[1][1]，所以最后要加一下
    return 0;
}
