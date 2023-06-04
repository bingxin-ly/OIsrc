#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int x[N], y[N], q[N];

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, z;
    cin >> n >> m >> z;

    int qsum = 0;
    for (int i = 1; i <= m; i++)
        cin >> x[i] >> y[i] >> q[i], qsum += q[i];
    sort(x + 1, x + m + 1), sort(y + 1, y + m + 1);
    int mid = m >> 1;
    mid += m % 2;

    int ans = qsum;
    for (int i = 1; i <= m; i++)
        ans += z * (abs(x[mid] - x[i]) + abs(y[mid] - y[i]));
    cout << ans << '\n'
         << x[mid] << ' ' << y[mid];
    return 0;
}