#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, k, a[N], b[N];
long long ans = LLONG_MAX, c[N];

long long calc(int l, int r)
{
    int m = (l + r) >> 1;
    if ((r - l + 1) & 1)
        return c[r] - c[m] - c[m - 1] + c[l - 1];
    else
        return c[r] - c[m] - c[m] + c[l - 1];
}
signed main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        c[i] = a[i] - b[i];
    sort(c + 1, c + n + 1);
    for (int i = 1; i <= n; i++)
        c[i] += c[i - 1];
    for (int i = 1; i <= k + 1; i++)
        ans = min(ans, calc(i, i + n - k - 1));
    cout << ans;
    return 0;
}