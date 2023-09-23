#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, greater<> > h;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1, x; i <= n; i++) cin >> x, h.emplace(x);
    int ans = 0, f1, f2;
    while (--n) {
        ans += f1 = h.top(), h.pop();
        ans += f2 = h.top(), h.pop();
        h.emplace(f1 + f2);
    }
    cout << ans;
    return 0;
}