#include <bits/stdc++.h>
using namespace std;

const int N = 105;
int a[N][N], f[N][N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++)
            for (int x = 1; x <= n; x++)
                for (int y = 1; y <= m; y++)
                    f[i][j] = max(f[i][j], a[x][y] - i * x - j * y);
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= m; y++)
        {
            int pre = 0x3f3f3f3f;
            for (int i = 0; i <= 100; i++)
                for (int j = 0; j <= 100; j++)
                    pre = min(pre, f[i][j] + i * x + j * y);
            if (pre != a[x][y])
                cout << "Impossible", exit(0);
        }

    cout << "Possible\n202 10401\n";
    for (int i = 1; i < 101; i++)
        cout << i << ' ' << i + 1 << " X\n";
    for (int i = 102; i < 202; i++)
        cout << i << ' ' << i + 1 << " Y\n";
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++)
            cout << i + 1 << ' ' << 202 - j << ' ' << f[i][j] << '\n';
    cout << "1 202";
    return 0;
}