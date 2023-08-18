#include <bits/stdc++.h>
using namespace std;

long long n, k, f[105], ans = 1;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 100; i >= k; i--)
    {
        f[i] = pow<long double>(n, 1.0 / i) - 1;
        for (int j = i << 1; j <= 100; j += i)
            f[i] -= f[j];
        ans += f[i];
    }
    cout << ans;
    return 0;
}