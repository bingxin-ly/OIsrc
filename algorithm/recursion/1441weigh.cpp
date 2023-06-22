#include <bits/stdc++.h>
using namespace std;

int w[20], dp[2005];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, ans = 0;
    cin >> n >> m;
    for (int &i : w)
        cin >> i;
    int cur = (1 << (n - m)) - 1, lim = (1 << n);
    while (cur < lim)
    {
        memset(dp, 0, sizeof dp), dp[0] = 1;
        int x = cur, i = 0, cnt = 0;
        while (i < n)
        {
            if (x & 1)
                for (int k = 2000; k >= 0; k--)
                    if (dp[k])
                        dp[k + w[i]] = 1;
            i++, x >>= 1;
        }
        for (int k = 1; k <= 2000; k++)
            cnt += dp[k];
        ans = max(ans, cnt);

        int lb = cur & -cur, rit = cur + lb;
        cur = ((rit ^ cur) >> (__builtin_ctz(lb) + 2)) | rit;
    }
    cout << ans;
    return 0;
}