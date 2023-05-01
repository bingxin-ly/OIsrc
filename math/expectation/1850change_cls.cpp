#include <bits/stdc++.h>
#define min(_a, _b) (_a < _b ? _a : _b)
using namespace std;

const int N = 2e3 + 10;
double p[10 * N], dis[N][N], dp[N][N][2];
int a[N][N], c[10 * N], d[10 * N];
void floyd(int v)
{
    for (int k = 1; k <= v; k++)
        for (int i = 1; i <= v; i++)
            for (int j = 1; j <= v; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}

int main()
{
    int n, m, v, e;
    cin >> n >> m >> v >> e;
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n; i++)
        cin >> d[i];
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    for (int i = 1; i <= v; i++)
        for (int j = 1; j < i; j++)
            dis[i][j] = dis[j][i] = 0x3f3f3f3f;

    for (int i = 1, a, b, c; i <= e; i++)
        cin >> a >> b >> c,
            dis[a][b] = dis[b][a] = min(dis[a][b], c);
    floyd(v);

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j][0] = dp[i][j][1] = 0x3f3f3f3f;

    dp[1][0][0] = dp[1][1][1] = 0;
    for (int i = 2; i <= n; i++)
    {
        double add = dis[c[i - 1]][c[i]];
        for (int j = 0, up = min(m, i); j <= up; j++)
        {
            dp[i][j][0] = min(dp[i - 1][j][0] + add, dp[i - 1][j][1] + dis[d[i - 1]][c[i]] * p[i - 1] + dis[c[i - 1]][c[i]] * (1 - p[i - 1]));
            if (j != 0)
                dp[i][j][1] = min(dp[i - 1][j - 1][0] + dis[c[i - 1]][d[i]] * p[i] + dis[c[i - 1]][c[i]] * (1 - p[i]), dp[i - 1][j - 1][1] + dis[c[i - 1]][c[i]] * (1 - p[i - 1]) * (1 - p[i]) + dis[c[i - 1]][d[i]] * (1 - p[i - 1]) * p[i] + dis[d[i - 1]][c[i]] * (1 - p[i]) * p[i - 1] + dis[d[i - 1]][d[i]] * p[i - 1] * p[i]);
        }
    }

    double ans = 0x3f3f3f3f;
    for (int i = 0; i <= m; i++)
        ans = min(ans, min(dp[n][i][0], dp[n][i][1]));
    printf("%.2lf", ans);
    return 0;
}