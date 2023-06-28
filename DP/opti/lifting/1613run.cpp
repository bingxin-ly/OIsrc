#include <bits/stdc++.h>
using namespace std;

const int N = 50 + 10, M = 1e4 + 10;
bool f[N][N][70];
int w[N][N];

int main()
{
    int n, m;
    cin >> n >> m;
    memset(w, 10, sizeof(w));
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        w[u][v] = 1;
        f[u][v][0] = true;
    }

    for (int k = 1; k <= 64; k++)
        for (int i = 1; i <= n; i++)
            for (int mid = 1; mid <= n; mid++)
                for (int j = 1; j <= n; j++)
                    if (f[i][mid][k - 1] && f[mid][j][k - 1])
                        f[i][j][k] = true, w[i][j] = 1;

    for (int mid = 1; mid <= n; mid++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                w[i][j] = min(w[i][j], w[i][mid] + w[mid][j]);

    cout << w[1][n];
    return 0;
}