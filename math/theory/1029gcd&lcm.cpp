#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int x, y, m, ans = 0;
    cin >> x >> y, m = x * y;
    for (int i = 1, u = sqrt(m); i <= u; i++)
        if (!(m % i) && __gcd(i, m / i) == x)
            ans += i == m / i ? 1 : 2;
    cout << ans;
    return 0;
}