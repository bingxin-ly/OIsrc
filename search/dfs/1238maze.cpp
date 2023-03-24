#include <bits/stdc++.h>
using namespace std;

bool suc;
int a[20][20], step[500][3], x2, y2;
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
void dfs(int i, int j, int t)
{
    if (!a[i][j])
        return;
    if (i == x2 && j == y2)
    {
        suc = true;
        for (int q = 1; q <= t - 1; q++)
            printf("(%d,%d)->", step[q][1], step[q][2]);
        printf("(%d,%d)\n", x2, y2);
        return;
    }
    step[t][1] = i, step[t][2] = j;
    a[i][j] = 0;
    for (int k = 0; k < 4; k++)
    {
        int x = i + dx[k], y = j + dy[k];
        dfs(x, y, t + 1);
    }
    step[t][1] = 0, step[t][2] = 0;
    a[i][j] = 1;
}
int main()
{
    int n, m, x1, y1;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    cin >> x1 >> y1 >> x2 >> y2;

    dfs(x1, y1, 1);

    if (!suc)
        puts("-1");
    return 0;
}
