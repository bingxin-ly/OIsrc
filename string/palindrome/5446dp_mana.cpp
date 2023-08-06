#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 5;
int n, R[N], f[N];
char s[N];

void solve()
{
    cin >> (s + 1), n = strlen(s + 1), s[0] = '#', s[n + 1] = '$';
    for (int i = 1, c = 0, r = 0; i <= n; i++)
    {
        R[i] = i <= r ? min(R[2 * c - i], r - i + 1) : 1;
        while (s[i - R[i]] == s[i + R[i]])
            R[i] += 1;
        if (r < i + R[i] - 1)
            r = i + R[i] - 1, c = i;
    }
    for (int i = n; i >= 1; i--)
    {
        f[i] |= 2 * i - 1 <= n && f[2 * i - 1] && i - R[i] + 1 == 1;
        f[i] |= i + R[i] - 1 == n;
    }
    for (int i = 1; i <= n; i++)
        if (f[i])
            cout << i << ' ', f[i] = 0;
    cout << '\n';
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