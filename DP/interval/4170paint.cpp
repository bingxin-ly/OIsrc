#include <bits/stdc++.h>
using namespace std;

constexpr int N = 55;
int n, f[N][N];
char a[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> (a + 1), n = strlen(a + 1);
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
        f[i][i] = 1;
    for (int l = 2; l <= n; l++)
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            if (a[i] == a[j])
                f[i][j] = min(f[i + 1][j], f[i][j - 1]);
            else
                for (int k = i; k < j; k++)
                    f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
        }
    cout << f[1][n];
    return 0;
}