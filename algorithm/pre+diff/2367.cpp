#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e6 + 9;
int n, p, a[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> p;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n; i >= 1; i--) a[i] -= a[i - 1];
    for (int x, y, z; p--;)
        cin >> x >> y >> z, a[x] += z, a[y + 1] -= z;
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];
    cout << *min_element(a + 1, a + n + 1);
    return 0;
}