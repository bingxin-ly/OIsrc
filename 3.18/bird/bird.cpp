#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10, M = 2e3 + 10, INF = 0x3f3f3f3f;

int n, m, k, x[N], y[N];
int cnt = 1, f[N][M];

struct pipe
{
    int p, l, h;
    bool operator<(const pipe &other) const { return p < other.p; }
} pipes[N];

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    for (int i = 1; i <= k; i++)
        cin >> pipes[i].p >> pipes[i].l >> pipes[i].h;
    sort(pipes + 1, pipes + k + 1);

    memset(f, 0x3f, sizeof(f));
    for (int j = 1; j <= m; j++)
        f[0][j] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = x[i] + 1; j <= x[i] + m; j++)
            f[i][j] = min(f[i - 1][j - x[i]] + 1, f[i][j - x[i]] + 1);
        for (int j = m + 1; j <= x[i] + m; j++)
            f[i][m] = min(f[i][m], f[i][j]);
        for (int j = 1; j <= m - y[i]; j++)
            f[i][j] = min(f[i][j], f[i - 1][j + y[i]]);
        if (i == pipes[cnt].p)
        {
            for (int j = 0; j <= pipes[cnt].l; j++)
                f[i][j] = INF;
            for (int j = pipes[cnt].h; j <= m; j++)
                f[i][j] = INF;

            int ans = INF;
            for (int j = 1; j <= m; j++)
                ans = min(ans, f[i][j]);
            if (ans == INF)
                return puts("0"), cout << cnt - 1, 0;
            cnt++;
        }
    }

    int ans = INF;
    for (int j = 1; j <= m; j++)
        ans = min(ans, f[n][j]);
        
    cout << 1 << '\n'
         << ans << endl;
    return 0;
}
