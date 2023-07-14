#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105, M = 1005;
int n, m, v[N], w[N], f[M];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];
    // 不拿就是 0，不用初始化！
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);
    cout << f[m];
    return 0;
}