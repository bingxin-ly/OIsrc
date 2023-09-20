#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int n;
pair<int, int> a[N];
vector<vector<int> > val;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first, a[i].second = i;
    sort(a + 1, a + n + 1);
    int l = 1, r = 1;
    while (r <= n) {
        vector<int> num;
        while (r <= n && a[r].first == a[l].first) num.emplace_back(a[r++].second);
        val.emplace_back(num), l = r;
    }
    int now = 0, pre = INT_MAX, cnt = 1;
    for (auto i : val) {
        if (!now) {
            if (pre >= i.back())
                pre = i.front();
            else
                pre = i.back(), now ^= 1;
        } else {
            if (pre <= i.front())
                pre = i.back();
            else
                pre = i.front(), now ^= 1, cnt++;
        }
    }
    cout << cnt;
    return 0;
}