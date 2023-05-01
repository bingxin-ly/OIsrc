#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, k, ans;
    cin >> n >> k;
    for (long long l = 1, r, t; l <= n; l = r + 1)
        r = (t = k / l) ? min(k / t, n) : n,
        ans -= t * (r - l + 1) * (l + r) >> 1;
    cout << ans + n * k;
    return 0;
}