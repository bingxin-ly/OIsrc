#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105, M = 1e4 + 5;
int n, m, v[N], f[M];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> v[i];
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = m - v[i]; j >= 0; j--)
            f[j + v[i]] += f[j];
    cout << f[m];
    return 0;
}