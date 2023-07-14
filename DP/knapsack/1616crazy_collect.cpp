#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 5, M = 1e7 + 5;
int n, m, v[N], w[N];
long long f[M];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];
    for (int i = 1; i <= n; i++)
        for (int j = v[i]; j <= m; j++)
            f[j] = max(f[j], f[j - v[i]] + w[i]);
    cout << f[m];
    return 0;
}