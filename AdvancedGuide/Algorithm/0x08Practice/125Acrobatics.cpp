#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e4 + 9;
int n;
pair<int, int> cow[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> cow[i].first >> cow[i].second;
    sort(cow + 1, cow + n + 1, [](auto x, auto y) {
        return x.first + x.second < y.first + y.second;
    });
    int sum = 0, ans = -1e9;
    for (int i = 1; i <= n; i++)
        ans = max(ans, sum - cow[i].second), sum += cow[i].first;
    cout << ans;
    return 0;
}