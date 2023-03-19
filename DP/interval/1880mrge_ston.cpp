#include <bits/stdc++.h>
using namespace std;

const int N = 3e2 + 10;
int n, maxl, minl = INT_MAX;
int maxf[N][N], minf[N][N];
int src[N], sum[N];

inline int get_sum(int i, int j)
{
    return sum[j] - sum[i - 1];
}
// 转移方程：f[i][j] = max(f[i][k]+f[k+1][j]+get_sum[i][j]);
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> src[i];
        src[i + n] = src[i]; // 存二倍，破环成链
    }
    for (int i = 1; i <= 2 * n; i++)
        sum[i] = sum[i - 1] + src[i]; // 计算前缀和
    for (int p = 1; p < n; p++)
        for (int i = 1, j = i + p; (j < n + n) && (i < n + n); i++, j = i + p)
        {
            minf[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                minf[i][j] = min(minf[i][j], minf[i][k] + minf[k + 1][j] + get_sum(i, j));
                maxf[i][j] = max(maxf[i][j], maxf[i][k] + maxf[k + 1][j] + get_sum(i, j));
            }
        }
    for (int i = 1; i <= n; i++)
    {
        minl = min(minl, minf[i][i + n - 1]);
        maxl = max(maxl, maxf[i][i + n - 1]);
    }
    cout << minl << endl
         << maxl << endl;
    return 0;
}