#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int p;
    cin >> p;
    while (p--) {
        int id, n;
        cin >> id >> n;
        cout << id << ' ' << (n + 1) / 2 << '\n';
        priority_queue<int, vector<int>, greater<>> sml;
        priority_queue<int, vector<int>, less<>> big;
        int x, cnt = 1;
        cin >> x, cout << x << ' ', sml.emplace(x);
        for (int i = 2; i <= n; i++) {
            cin >> x;
            if (x < sml.top())
                big.emplace(x);
            else
                sml.emplace(x);
            int s = big.size();
            if (s > i / 2) sml.emplace(big.top()), big.pop();
            if (s < i / 2) big.emplace(sml.top()), sml.pop();
            if (i & 1) cout << sml.top() << (++cnt % 10 == 0 ? '\n' : ' ');
        }
        if (cnt % 10) cout << '\n';
    }
    return 0;
}