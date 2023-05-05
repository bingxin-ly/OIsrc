#include <bits/stdc++.h>
using namespace std;

double a[20][20], b[20], c[20][20], eps = 1e-7;
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            c[i][j] = 2 * (a[i][j] - a[i + 1][j]);
            b[i] += a[i][j] * a[i][j] - a[i + 1][j] * a[i + 1][j];
        }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
            if (abs(c[j][i]) > eps)
            {
                for (int k = 1; k <= n; k++)
                    swap(c[i][k], c[j][k]);
                swap(b[i], b[j]);
            }
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            double k = c[j][i] / c[i][i];
            for (int l = i; l <= n; l++)
                c[j][l] -= c[i][l] * k;
            b[j] -= b[i] * k;
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%.3lf ", b[i] / c[i][i]);
    return 0;
}