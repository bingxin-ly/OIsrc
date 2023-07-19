#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105, M = 2e4 + 5, T = 1e4;
int n, m, a[N];
int f[N][M], ans[N]; // f: 前 i 个数能否凑成 j ，能为 1（正数）或 -1（负数），不能为 0
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    f[1][a[1] + T] = 1, f[2][a[1] - a[2] + T] = -1;
    for (int i = 3; i <= n; i++)
        for (int j = 0; j <= T << 1; j++)
            if (f[i - 1][j])
                f[i][j + a[i]] = 1, f[i][j - a[i]] = -1;
    int v = m + T;
    for (int i = n; i > 1; i--)
        ans[i] = f[i][v], v -= ans[i] * a[i];
    int cnt = 0;
    for (int i = 2; i <= n; i++)
        if (ans[i] == 1)
            cout << i - cnt - 1 << '\n', cnt++;
    for (int i = 2; i <= n; i++)
        if (ans[i] == -1)
            cout << "1\n";
    return 0;
}