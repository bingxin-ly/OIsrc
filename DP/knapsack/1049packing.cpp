#include <bits/stdc++.h>
using namespace std;

constexpr int N = 35, V = 2e4 + 5;
int n, m, f[V];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m >> n;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        for (int j = m; j >= x; j--)
            f[j] = max(f[j], f[j - x] + x);
    }
    cout << m - f[m];
    return 0;
}