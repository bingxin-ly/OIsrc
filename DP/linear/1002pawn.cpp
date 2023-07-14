#include <bits/stdc++.h>
using namespace std;

int n, m, x, y;
int dx[] = {-2, -2, -1, -1, 0, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, 0, -2, 2, -1, 1};
long long f[30][30];
bool check(int a, int b)
{
    for (int i = 0; i < 9; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || ny < 0)
            continue;
        else if (nx == a && ny == b)
            return true;
    }
    return false;
}
int main()
{
    cin >> n >> m >> x >> y;
    f[0][0] = 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
        {
            if (!i && !j)
                continue;
            if (check(i, j))
                continue;
            if (!i)
                f[i][j] = f[i][j - 1];
            else if (!j)
                f[i][j] = f[i - 1][j];
            else
                f[i][j] = f[i - 1][j] + f[i][j - 1];
        }
    cout << f[n][m] << endl;
    return 0;
}