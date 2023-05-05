#include <bits/stdc++.h>
using namespace std;

double mat[110][110], ans[110], eps = 1e-7;
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            cin >> mat[i][j];

    for (int i = 1; i <= n; i++)
    {
        int r = i;
        for (int j = i + 1; j <= n; j++)
            if (abs(mat[r][i]) < abs(mat[j][i]))
                r = j;
        if (abs(mat[r][i]) < eps)
            puts("No Solution"), exit(0);

        if (i != r)
            swap(mat[i], mat[r]);
        double div = mat[i][i];
        for (int j = i; j <= n + 1; j++)
            mat[i][j] /= div;
        for (int j = i + 1; j <= n; j++)
        {
            div = mat[j][i];
            for (int k = i; k <= n + 1; k++)
                mat[j][k] -= mat[i][k] * div;
        }
    }

    ans[n] = mat[n][n + 1];
    for (int i = n - 1; i >= 1; i--)
    {
        ans[i] = mat[i][n + 1];
        for (int j = i + 1; j <= n; j++)
            ans[i] -= (mat[i][j] * ans[j]);
    }
    for (int i = 1; i <= n; i++)
        printf("%.2lf\n", ans[i]);
    return 0;
}