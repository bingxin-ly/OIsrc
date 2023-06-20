// 深搜加动态规划
#include <bits/stdc++.h>
using namespace std;

int n, k, ans;
int a[20], b[20], dp[2000];

int calc(int x, int sum)
{
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    for (int i = 1; i <= x; i++)
        for (int j = b[i]; j <= n * sum; j++)
            dp[j] = min(dp[j], dp[j - b[i]] + 1);
    for (int i = 1; i <= n * sum; i++)
        if (dp[i] > n)
            return i - 1;
    return n * sum;
}
void dfs(int x, int pre, int mxn, int sum) // 枚举面值
{
    if (x == k + 1)
    {
        if (ans < mxn)
        {
            ans = mxn;
            for (int i = 1; i <= k; i++)
                a[i] = b[i];
        }
        return;
    }
    for (int i = pre + 1; i <= mxn + 1; i++)
    {
        b[x] = i;
        dfs(x + 1, i, calc(x, sum + i), sum + i);
    }
}

signed main()
{
    cin >> n >> k;
    dfs(1, 0, 0, 0);
    for (int i = 1; i <= k; i++)
        cout << a[i] << ' ';
    cout << "\nMAX=" << ans;
    return 0;
}