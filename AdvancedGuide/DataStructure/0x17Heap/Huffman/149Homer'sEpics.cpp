#include <bits/stdc++.h>
using namespace std;
using llong = long long;
using pll = pair<llong, llong>;

llong n, k, x;
priority_queue<pll, vector<pll>, greater<> > q;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> x, q.emplace(x, 0);
    while ((n - 1) % (k - 1))
        n++, q.emplace(0, 0);

    llong ans = 0;
    while (q.size() != 1) {
        llong num = 0, dep = 0;
        for (int i = 1; i <= k; i++) {
            num += q.top().first;
            dep = max(dep, q.top().second);
            q.pop();
        }
        ans += num, q.emplace(num, dep + 1);
    }
    cout << ans << '\n'
         << q.top().second;
    return 0;
}