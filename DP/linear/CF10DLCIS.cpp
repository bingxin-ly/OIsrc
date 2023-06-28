#include <bits/stdc++.h>
using namespace std;

int a[505], b[505];
int f[505][505]; // 表示 A1 ~ Ai 与 B1 ~ Bj 可以构成的以 Bj 为结尾的 LCIS 的长度
signed force()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i] != b[j])
                f[i][j] = f[i - 1][j];
            else
                for (int k = 0; k < j; k++)
                    if (b[k] < a[i])
                        f[i][j] = max(f[i][j], f[i - 1][k] + 1);
    int ans = 0;
    for (int j = 1; j <= n; j++)
        ans = max(ans, f[n][j]);
    cout << ans;
    return 0;
}
int n, pos[505][505];
void print(int p)
{
    if (!p)
        return;
    print(pos[n][p]);
    cout << b[p] << ' ';
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int m;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
    {
        int p = 0;
        for (int j = 1; j <= m; j++)
        {
            if (a[i] != b[j])
                f[i][j] = f[i - 1][j], pos[i][j] = pos[i - 1][j];
            else
                f[i][j] = f[i - 1][p] + 1, pos[i][j] = p;
            if (b[j] < a[i] && f[i - 1][j] >f[i - 1][p])
                p = j;
        }
    }
    int p = 0;
    for (int j = 1; j <= m; j++)
        if (f[n][j] > f[n][p])
            p = j;
    cout << f[n][p] << '\n', print(p);
    return 0;
}