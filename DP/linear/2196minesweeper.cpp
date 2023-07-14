#include <bits/stdc++.h>
using namespace std;

constexpr int N = 25;
int n, w[N], g[N][N], f[N], b[N];
// f[i] 为以 i 结尾时挖到地雷的最大值

void print(int i)
{
    if (!i)
        return;
    print(b[i]);
    cout << i << ' ';
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            cin >> g[i][j];
    f[1] = w[1];
    for (int i = 2; i <= n; i++)
    {
        f[i] = w[i];
        for (int j = 1; j < i; j++)
            if (g[j][i] && f[j] + w[i] > f[i])
                f[i] = f[j] + w[i], b[i] = j;
    }
    int ans = 0, tail = 0;
    for (int i = 1; i <= n; i++)
        if (ans < f[i])
            ans = f[i], tail = i;
    print(tail);
    cout << '\n'
         << ans;
    return 0;
}