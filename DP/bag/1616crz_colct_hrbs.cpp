#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;

int n, m;
int v[N], w[N];
long long f[N];

int main()
{
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = v[i]; j <= m; j++)
            f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[m] << endl;
}

int g[N][N];

int main_deprecated()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k * v[i] <= j; k++)
                g[i][j] = max(g[i][j], g[i - 1][j - v[i] * k] + w[i] * k);

    cout << g[n][m] << endl;
    return 0;
}
