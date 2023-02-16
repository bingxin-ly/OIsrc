#include <bits/stdc++.h>
using namespace std;

const int N = 60;
int n, c;
int loc[N], sum[N];
int f[N][N][2];

int cal(int i, int j, int l, int r)
{
    return (loc[j] - loc[i]) * (sum[l] + sum[n] - sum[r - 1]);
}

int main()
{
    cin >> n >> c;
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        cin >> a >> b;
        loc[i] = a;
        sum[i] = sum[i - 1] + b;
    }
    f[c][c][0] = f[c][c][1] = 0;
    for (int j = c; j <= n; j++)
        for (int i = j - 1; i > 0; i--)
        {
            f[i][j][0] = min(f[i + 1][j][0] + cal(i, i + 1, i, j + 1), f[i + 1][j][1] + cal(i, j, i, j + 1));
            f[i][j][1] = min(f[i][j - 1][0] + cal(i, j, i - 1, j), f[i][j - 1][1] + cal(j - 1, j, i - 1, j));
        }
    cout << min(f[1][n][0], f[1][n][1]) << endl;
    return 0;
}
