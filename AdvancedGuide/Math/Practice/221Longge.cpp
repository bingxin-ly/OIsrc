#include <bits/stdc++.h>
using namespace std;

unsigned phi(unsigned n) {
    unsigned r = n;
    for (unsigned i = 2; i <= n / i; i++)
        if (!(n % i)) {
            r = r / i * (i - 1);
            while (!(n % i)) n /= i;
        }
    if (n != 1) r = r / n * (n - 1);
    return r;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    unsigned n;
    cin >> n;
    long long ans = 0;
    for (unsigned i = 1; i <= n / i; i++)
        if (!(n % i)) {
            ans += i * phi(n / i);
            if (i != n / i) ans += n / i * phi(i);
        }
    cout << ans;
    return 0;
}