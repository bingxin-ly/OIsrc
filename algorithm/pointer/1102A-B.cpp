#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 9;
int n, c, a[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> c;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    long long ans = 0;
    for (int i = 1, j = 1, k = 1; i <= n; i++) {
        while (j <= n && a[j] - a[i] < c) j++;
        while (k <= n && a[k] - a[i] <= c) k++;
        if (a[j] - a[i] == c && a[k - 1] - a[i] == c) ans += k - j;
    }
    cout << ans;
    return 0;
}