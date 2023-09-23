#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 9;
int n;
struct Goods {
    int p, d;
    friend bool operator<(Goods x, Goods y) { return x.d != y.d ? x.d < y.d : x.p < y.p; }
} a[N];

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n) {
        for (int i = 1; i <= n; i++) cin >> a[i].p >> a[i].d;
        sort(a + 1, a + n + 1);
        priority_queue<int, vector<int>, greater<> > q;
        for (int i = 1; i <= n; i++) {
            if (a[i].d == (int)q.size()) q.pop();
            q.emplace(a[i].p);
        }
        int ans = 0;
        while (!q.empty()) ans += q.top(), q.pop();
        cout << ans << '\n';
    }
    return 0;
}