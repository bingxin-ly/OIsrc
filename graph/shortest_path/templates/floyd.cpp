// 不可用于负权边
#include <bits/stdc++.h>
#define chkmin(a, b) a = min(a, b)
using namespace std;

const int MAXN = 3e3 + 10, MAXM = 6e3 + 10;

int n, m;
int f[MAXN][MAXN];

int main()
{
    cin >> n >> m;
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
        f[i][i] = 0;
    for (int i = 0, u, v, w; i < m; i++)
        cin >> u >> v >> w, chkmin(f[u][v], w);

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                chkmin(f[i][j], f[i][k] + f[k][j]);

    ssize_t ans;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            ans += j * f[i][j];
        cout << ans << endl, ans = 0;
    }
}
