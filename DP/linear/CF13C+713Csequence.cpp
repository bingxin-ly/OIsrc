#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5005;
int n, a[N], b[N], f[2][N];
signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i]/* 非增去掉后面 */, b[i] = a[i];
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
    {
        int o = i & 1, minv = LLONG_MAX;
        for (int j = 1; j <= n; j++)
        {
            minv = min(minv, f[!o][j]);
            f[o][j] = minv + abs(a[i] - b[j]);
        }
    }
    int res = LLONG_MAX;
    for (int i = n & 1, j = 1; j <= n; j++)
        res = min(res, f[i][j]);
    cout << res;
    return 0;
}