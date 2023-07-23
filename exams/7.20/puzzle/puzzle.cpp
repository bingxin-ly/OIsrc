#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 1e6 + 5;
char ori[N];
int n, arr[N], sum[N];
int tot[2], cnt, ans;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> n >> (ori + 1);
    for (int i = 1; i <= n; i++)
        arr[i] = ori[i] - '0',
        sum[i] = sum[i - 1] + arr[i],
        ans -= arr[i];

    cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (sum[i] & 1)
            ans += tot[1] + 1, tot[0]++;
        else
            ans += tot[0], tot[1]++;
    }
    cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!arr[i])
            cnt++;
        else
            ans -= cnt, cnt = 0;
    }
    cnt = 0;
    for (int i = n; i > 0; i--)
    {
        if (!arr[i])
            cnt++;
        else
            ans -= cnt, cnt = 0;
    }
    cout << ans;
    return 0;
}