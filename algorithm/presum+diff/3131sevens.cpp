#include <bits/stdc++.h>
using namespace std;

// 不能暴力循环枚举长度...若两个数相减 mod 7 为 0，那么这两个数 mod 7 的余数一定相同！！
const int N = 5e4 + 10;
int sum[N], r[7];

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    memset(r, -1, sizeof r), r[0] = 0;
    int n, ans = 0;
    cin >> n;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x, (sum[i] = sum[i - 1] + x) %= 7;
        int &rmd = r[sum[i]];
        if (rmd == -1)
            rmd = i;
        ans = max(ans, i - rmd);
    }
    cout << ans;
    return 0;
}