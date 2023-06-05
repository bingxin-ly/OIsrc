#include <bits/stdc++.h>
using namespace std;

signed main()
{
    int n, pre;
    cin >> n >> pre;
    int ans = pre;
    for (int i = 2, x; i <= n; i++)
    {
        cin >> x;
        if (x > pre)
            ans += x - pre;
        pre = x;
    }
    cout << ans;
    return 0;
}