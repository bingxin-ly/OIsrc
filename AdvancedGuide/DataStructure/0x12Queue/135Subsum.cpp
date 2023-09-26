#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 9;
int n, m, s[N], q[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1];
    int l = 1, r = 1, ans = INT_MIN;
    for (int i = 1; i <= n; i++) {
        while (l <= r && i - q[l] > m) l++;
        ans = max(ans, s[i] - s[q[l]]);
        while (l <= r && s[q[r]] >= s[i]) r--;
        q[++r] = i;
    }
    cout << ans;
    return 0;
}