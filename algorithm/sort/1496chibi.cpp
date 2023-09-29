#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e4 + 9;
int n, l[N], r[N], a[N << 1];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    vector<int> num;
    for (int i = 1; i <= n; i++)
        cin >> l[i] >> r[i], num.emplace_back(l[i]), num.emplace_back(r[i]);
    sort(num.begin(), num.end()), num.erase(unique(num.begin(), num.end()), num.end());
    for (int i = 1; i <= n; i++) {
        l[i] = lower_bound(num.begin(), num.end(), l[i]) - num.begin() + 1;
        r[i] = lower_bound(num.begin(), num.end(), r[i]) - num.begin() + 1;
        a[l[i]] += 1, a[r[i]] -= 1;
    }
    n = num.size();
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];
    int l = 1, ans = 0;
    while (l <= n) {
        int r = l;
        while (r <= n && a[r]) r++;
        ans += num[r - 1] - num[l - 1], l = r;
        while (l <= n && !a[l]) l++;
    }
    cout << ans;
    return 0;
}