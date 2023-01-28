#include <bits/stdc++.h>
using namespace std;

#define M 19650827

int n;
int f[2010][2010][2];
int que[1010];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", que + i);
    for (int i = 1; i <= n; i++)
        f[i][i][0] = 1;
    for (int x = 1; x <= n; x++)
        for (int i = 1, j = i + x; j <= n; i++, j++)
        {
            if (que[i] < que[i + 1])
                f[i][j][0] += f[i + 1][j][0];
            if (que[i] < que[j])
                f[i][j][0] += f[i + 1][j][1];
            if (que[j] > que[i])
                f[i][j][1] += f[i][j - 1][0];
            if (que[j] > que[j - 1])
                f[i][j][1] += f[i][j - 1][1];
            f[i][j][0] %= M;
            f[i][j][1] %= M;
        }

    printf("%d", (f[1][n][0] + f[1][n][1]) % M);
}
