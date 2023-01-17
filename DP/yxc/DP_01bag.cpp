#include <bits/stdc++.h>
using namespace std;

const int MAX = 1010;

int N, V;
int v[MAX], w[MAX];
int f[MAX][MAX];

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];
    for (int i = 1; i <= N; i++)
        for (int j = 0; j <= V; j++)
        {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])
                f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
        }
    cout << f[N][V] << endl;
    return 0;
}

int g[MAX];

int main(int argc, char **argv)
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];
    for (int i = 1; i <= N; i++)
        for (int j = V; j >= v[i]; j--)
            g[j] = max(g[j], g[j - v[i]] + w[i]);
    cout << g[V] << endl;
}