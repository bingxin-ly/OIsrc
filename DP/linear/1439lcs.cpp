#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, a[N], b[N], c[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], c[a[i]] = i;
    for (int i = 1; i <= n; i++) cin >> b[i], b[i] = c[b[i]];
    vector<int> s;
    s.emplace_back(b[1]);
    for (int i = 2; i <= n; i++)
        if (b[i] > s.back())
            s.emplace_back(b[i]);
        else
            *lower_bound(s.begin(), s.end(), b[i]) = b[i];
    cout << s.size();
    return 0;
}