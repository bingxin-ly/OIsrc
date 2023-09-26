#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9;
int n, k, a[N], q[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int l = 1, r = 0;
    for (int i = 1; i <= n; i++) {
        while (l <= r && i - q[l] + 1 > k) l++;
        while (l <= r && a[q[r]] >= a[i]) r--;
        q[++r] = i;
        if (i >= k) cout << a[q[l]] << ' ';
    }
    cout << '\n', l = 1, r = 0;
    for (int i = 1; i <= n; i++) {
        while (l <= r && i - q[l] + 1 > k) l++;
        while (l <= r && a[q[r]] <= a[i]) r--;
        q[++r] = i;
        if (i >= k) cout << a[q[l]] << ' ';
    }
    return 0;
}