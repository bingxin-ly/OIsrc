#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

constexpr int N = 1e5 + 9;
int n, m;
pair<int, int> a[N], b[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
        for (int i = 1; i <= m; i++) cin >> b[i].x >> b[i].y;
        sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
        multiset<int> mac;
        long long cnt = 0, ans = 0;
        for (int i = m, j = n; i; i--) {
            while (j && a[j].x >= b[i].x) mac.emplace(a[j--].y);
            auto it = mac.lower_bound(b[i].y);
            if (it != mac.end())
                cnt += 1, ans += 500 * b[i].x + 2 * b[i].y, mac.erase(it);
        }
        cout << cnt << ' ' << ans << '\n';
    }
    return 0;
}