#include <bits/stdc++.h>
using namespace std;

int n, f[32];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        int maxn = 0;
        for (int i = 0; i <= 30; i++)
            if ((1 << i) & x)
                maxn = max(maxn, f[i] + 1);
        for (int i = 0; i <= 30; i++)
            if ((1 << i) & x)
                f[i] = maxn;
    }
    int ans = 0;
    for (int i = 0; i <= 30; i++)
        ans = max(ans, f[i]);
    cout << ans;
    return 0;
}