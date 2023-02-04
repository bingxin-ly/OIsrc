#include <bits/stdc++.h>
using namespace std;

// 二进制优化
const int N = 25000, M = 2010;

int n, m;
int v[N], w[N];
int f[N];

int main()
{
    cin >> n >> m;

    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        int a, b, s;
        cin >> a >> b >> s;
        int k = 1;
        while (k <= s)
        {
            cnt++;
            v[cnt] = a * k;
            w[cnt] = b * k;
            s -= k;
            k *= 2;
        }
        if (s > 0)
        {
            cnt++;
            v[cnt] = a * s;
            w[cnt] = b * s;
        }
    }

    n = cnt;

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[m] << endl;
    return 0;
}

// 朴素方法
// const int N = 1e2 + 10;
// int s[N], g[N][N];

// int main_deprecated()
// {
//     cin >> n >> m;

//     for (int i = 1; i <= n; i++)
//         cin >> v[i] >> w[i] >> s[i];

//     for (int i = 1; i <= n; i++)
//         for (int j = 0; j <= m; j++)
//             for (int k = 0; k <= s[i] && k * v[i] <= j; k++)
//                 g[i][j] = max(g[i][j], g[i - 1][j - v[i] * k] + w[i] * k);

//     cout << g[n][m] << endl;
//     return 0;
// }