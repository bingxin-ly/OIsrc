#include <bits/stdc++.h>
using namespace std;

int s[10005];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> s[i], s[i] <<= 1;
    for (int i = 1, x, y, v; i <= m; i++)
        cin >> x >> y >> v, s[x] += v, s[y] += v;
    sort(s + 1, s + n + 1);
    while (n)
        ans += s[n] - s[n - 1], n -= 2;
    cout << ans / 2;
    return 0;
}