int n, m;         // n、m为题中最大值
int matrix[n][m]; // 全局矩阵数组
int vis[n][m];    // 访问去重
// 所在点的偏移量（4个或8个）
int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};

// 核心dfs算法（递归实现）
void dfs(int x, int y)
{
    for (int i = 0; i < 4(/ 8); i++)
    {
        int xx = x + dx[i];
        int yy = y + dy[i];
        // 矩阵越界判断
        if (xx < 0 || yy < 0 || xx > n || yy > m)
            continue;
        // 相似类型判断
        if (matrix[xx][yy] != 0)
            continue;
        if (vis[xx][yy] == 1)
            continue;
        else
            vis[xx][yy] = 1;
        // 符合条件时做的事
        matrix[xx][yy];
        // 下一层
        dfs(xx, yy);
    }
}
void search_0(int &x, int &y)
{
    for (int i = 0; i < n + 2; i++)
        for (int j = 0; j < n + 2; j++)
            if (matrix[i][j] == 0)
            {
                x = i,
                y = j;
                return;
            }
}
