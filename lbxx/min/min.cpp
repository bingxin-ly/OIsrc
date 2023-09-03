#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
long long n, s[N];
multiset<pair<long long, int>> psum;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1];

    long long ans = LLONG_MAX, len = 0;
    psum.emplace(0, 0);
    for (int i = 1; i <= n; i++) {
        auto p = psum.lower_bound({s[i], i});
        if (p != psum.end()) {
            int val = abs(s[i] - p->first);
            if (ans > val || (ans == val) && len < i - p->second)
                ans = val, len = i - p->second;
        }
        if (p != psum.begin()) {
            int val = abs(s[i] - (--p)->first);
            if (ans > val || (ans == val) && len < i - p->second)
                ans = val, len = i - p->second;
        }
        psum.emplace(s[i], i);
    }
    cout << ans << '\n' << len;
    return 0;
}