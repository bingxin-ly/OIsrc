#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
constexpr double eps = 1e-6;
int n, s, t;
int o[N], a[N], b[N], k[N];
int c[N], x[N];

bool dijk(double T)
{
    
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> s >> t;
    for (int i = 1; i <= s; i++)
        cin >> o[i] >> a[i] >> b[i] >> k[i];
    for (int i = 1; i <= t; i++)
        cin >> c[i] >> x[i];
    if (!dijk(0))
        return cout << -1, 0;
    double l = 0, r = 1e9;
    while (r - l > eps)
    {
        double m = (l + r) / 2;
        dijk(m) ? l = m : r = m;
    }
    cout << fixed << setprecision(6) << l;
    return 0;
}