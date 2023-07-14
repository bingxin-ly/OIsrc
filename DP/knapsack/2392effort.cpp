#include <bits/stdc++.h>
using namespace std;

int s[5], a[25], f[1500];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (int i = 1; i <= 4; i++)
        cin >> s[i];
    int ans = 0;
    for (int i = 1; i <= 4; i++)
    {
        memset(f, 0, sizeof(f));
        int sum = 0;
        for (int j = 1; j <= s[i]; j++)
            cin >> a[j], sum += a[j];
        for (int j = 1; j <= s[i]; j++)
            for (int k = sum >> 1; k >= a[j]; k--)
                f[k] = max(f[k], f[k - a[j]] + a[j]);
        ans += sum - f[sum >> 1];
    }
    cout << ans;
    return 0;
}