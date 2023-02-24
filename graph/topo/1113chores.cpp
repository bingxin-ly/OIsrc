#include <bits/stdc++.h>
using namespace std;

int n, l, t, ans[10005], maxn;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> l >> l;
        int tmp = 0;
        while (cin >> t && t)
            tmp = max(ans[t], tmp);
        ans[i] = tmp + l;
        maxn = max(ans[i], maxn);
    }
    cout << maxn << endl;
    return 0;
}
