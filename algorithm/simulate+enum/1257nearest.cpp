#include <bits/stdc++.h>
using namespace std;

inline long long square(int a) { return 1ll * a * a; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;

    double ans = 1e18;
    for (int i = 0; i < points.size(); i++)
        for (int j = i + 1; j < points.size(); j++)
            ans = min(ans, sqrt(square(points[i].first - points[j].first) +
                                square(points[i].second - points[j].second)));

    cout << fixed << setprecision(4) << ans;
    return 0;
}