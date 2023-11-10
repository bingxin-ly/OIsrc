#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int n;
vector<pair<int, int> > a;
vector<int> b;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (x <= i) a.emplace_back(i - x, x);
    }
    if (a.empty()) return cout << 0, 0;
    sort(a.begin(), a.end());
    b.emplace_back(a[0].second);
    for (int i = 1; i < (int)a.size(); i++)
        if (a[i].second > b.back())
            b.emplace_back(a[i].second);
        else
            *lower_bound(b.begin(), b.end(), a[i].second) = a[i].second;
    cout << b.size();
    return 0;
}