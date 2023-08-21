#include <bits/stdc++.h>
using namespace std;

constexpr int N = 6e3 + 5;
int n, u[N], v[N], w[N], e[N];
int p[N], s[N];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

void solve()
{
    cin >> n;
    for (int i = 1; i < n; i++)
        cin >> u[i] >> v[i] >> w[i], e[i] = i;
    iota(p + 1, p + n + 1, 1), fill(s + 1, s + n + 1, 1);
    sort(e + 1, e + n, [](int x, int y)
         { return w[x] < w[y]; });
    int ans = 0;
    for (int i = 1; i < n; i++)
    {
        int x = find(u[e[i]]), y = find(v[e[i]]);
        ans += (s[x] * s[y] - 1) * (w[e[i]] + 1);
        p[y] = x, s[x] += s[y];
    }
    cout << ans << '\n';
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}