#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
namespace TRI
{
    int a[N], b[N], f[N], sl[N], sr[N];
    int cost(int l, int r)
    {
        sl[l - 1] = sr[l - 1] = 0;
        for (int k = l; k <= r; k++)
            sl[k] = sl[k - 1] + abs(a[k] - a[l - 1]);
        for (int k = l; k <= r; k++)
            sr[k] = sr[k - 1] + abs(a[k] - a[r + 1]);
        int ret = INT_MAX;
        for (int k = l - 1; k <= r; k++)
            ret = min(ret, sl[k] - sl[l - 1] + sr[r] - sr[k]);
        return ret;
    }
    signed main()
    {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        memset(f, 0x3f, sizeof f), f[0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                if (a[j] <= a[i]) // O(n^3) 转移
                    f[i] = min(f[i], f[j] + cost(j + 1, i - 1));
        int ans = INT_MAX;
        for (int i = 1; i <= n; i++)
        {
            int j = 0;
            for (int k = i + 1; k <= n; k++)
                j += abs(a[k] - a[i]);
            ans = min(ans, j + f[i]);
        }
        cout << ans;
        return 0;
    }
}
namespace BI
{
    int a[N], b[N], f[N][N];
    int solve(const int a[], int n)
    {
        memcpy(b + 1, a + 1, n * sizeof(int));
        sort(b + 1, b + n + 1);
        for (int i = 1; i <= n; i++)
        {
            int minv = INT_MAX;
            for (int j = 1; j <= n; j++)
            {
                minv = min(minv, f[i - 1][j]);
                f[i][j] = minv + abs(a[i] - b[j]);
            }
        }
        int ret = INT_MAX;
        for (int j = 1; j <= n; j++)
            ret = min(ret, f[n][j]);
        return ret;
    }
    signed main()
    {
        // 如果递增是最好的，这样状态设计必须要表示出我这里填什么
        // 预处理 c 为 a 排序后的数组，于是有 f[i][j] 表示处理到 bi，令 BI = ci 的最小值
        // 于是有：f[i][j] = min{0<=k<=j}(f[i-1][k]) + |A_i-C_j|
        // j 在扩展时，显然只会多出来一个点，所以可以维护一下 O(1) 转移
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        int a1 = solve(a, n);
        reverse(a + 1, a + n + 1);
        int a2 = solve(a, n);
        cout << min(a1, a2);
        return 0;
    }
}
signed main() { return BI::main(); }