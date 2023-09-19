#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, a[N], ans;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n, m = (1 + n) >> 1;
    for (int i = 1; i <= n; i++) cin >> a[i];
    nth_element(a + 1, a + m, a + n + 1);
    for (int i = 1; i <= n; i++) ans += abs(a[i] - a[m]);
    cout << ans;
    return 0;
}