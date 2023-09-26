#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2005;
int n, d, c;
pair<double, double> r[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> d;
    double z, pos = -1e18;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if (y > d) return cout << -1, 0;
        z = sqrt(d * d - y * y), r[i] = {x - z, x + z};
    }
    sort(r + 1, r + n + 1);
    for (int i = 1; i <= n; i++) {
        if (r[i].first > pos)
            c++, pos = r[i].second;
        else
            pos = min(pos, r[i].second);
    }
    cout << c;
    return 0;
}