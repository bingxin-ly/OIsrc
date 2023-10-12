#include <bits/stdc++.h>
using namespace std;

double n, a[8]{1};
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (int i = 1; i <= 7; i++) cin >> a[i], n += a[i];
    for (int i = 1; i <= 6; i++) 
        a[0] *= a[i] / (n - i + 1);
    cout << fixed << setprecision(3) << 5040 * a[0] * a[7];
    return 0;
}