#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, q, u, v, t, a[N];
queue<int> qw[4];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> q >> u >> v >> t;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1, greater<>());
    for (int i = 1; i <= n; i++) qw[1].emplace(a[i]);

    for (int i = 0; i < m; i++) {
        pair<int, int> p = max<pair<int, int>>({
            {qw[1].empty() ? INT_MIN : qw[1].front(), 1},
            {qw[2].empty() ? INT_MIN : qw[2].front(), 2},
            {qw[3].empty() ? INT_MIN : qw[3].front(), 3},
        });
        qw[p.second].pop();

        int x = p.first + q * i, y = 1ll * x * u / v, z = x - y;
        qw[2].emplace(y - q - q * i), qw[3].emplace(z - q - q * i);

        if (!((i + 1) % t)) cout << x << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= n + m; i++) {
        pair<int, int> p = max<pair<int, int>>({
            {qw[1].empty() ? INT_MIN : qw[1].front(), 1},
            {qw[2].empty() ? INT_MIN : qw[2].front(), 2},
            {qw[3].empty() ? INT_MIN : qw[3].front(), 3},
        });
        qw[p.second].pop();
        if (!(i % t)) cout << p.first + q * m << ' ';
    }
    return 0;
}