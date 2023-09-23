#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2009;
int n, m, a[N], b[N], c[N];

void solve() {
    priority_queue<pair<int, pair<int, int> > > q;
    q.emplace(-a[1] - b[1], make_pair(1, 1));
    for (int i = 1; i <= n; i++) {
        c[i] = -q.top().first;
        auto [x, y] = q.top().second;
        q.pop();
        if (y == 1) q.emplace(-a[x + 1] - b[y], make_pair(x + 1, y));
        q.emplace(-a[x] - b[y + 1], make_pair(x, y + 1));
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> m >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        sort(a + 1, a + n + 1);
        while (--m) {
            for (int i = 1; i <= n; i++) cin >> b[i];
            sort(b + 1, b + n + 1);
            solve(), memcpy(a, c, sizeof(c));
        }
        for (int i = 1; i <= n; i++) cout << a[i] << ' ';
        cout << '\n';
    }
    return 0;
}