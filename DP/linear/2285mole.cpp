#include <bits/stdc++.h>
using namespace std;

constexpr int M = 1e4 + 5;
int n, m, f[M];
struct
{
    int t, x, y;
} s[M];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> s[i].t >> s[i].x >> s[i].y;
    fill(f + 1, f + m + 1, 1);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j < i; j++)
            if (s[i].t - s[j].t >= abs(s[i].x - s[j].x) + abs(s[i].y - s[j].y))
                f[i] = max(f[i], f[j] + 1);
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans = max(ans, f[i]);
    cout << ans;
    return 0;
}