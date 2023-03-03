#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3402, MAXV = 12880;

int N, V;
int v[MAXN], w[MAXN];
int f[MAXV];

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];
    for (int i = 1; i <= N; i++)
        for (int j = V; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);
    cout << f[V] << endl;
    return 0;
}

// 朴素方法
int g[MAXN][MAXV];

int main_deprecated()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];
    for (int i = 1; i <= N; i++)
        for (int j = 0; j <= V; j++)
        {
            g[i][j] = g[i - 1][j];
            if (j >= v[i])
                g[i][j] = max(g[i][j], g[i - 1][j - v[i]] + w[i]);
        }
    cout << g[N][V] << endl;
    return 0;
}
