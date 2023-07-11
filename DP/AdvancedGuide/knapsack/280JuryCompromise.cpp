#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205, M = 25;
int n, m, T;
namespace bad
{
    int P[N], D[N];
    bool f[M][20 * M][20 * M];

    void solve()
    {
        for (int i = 1; i <= n; i++)
            cin >> P[i] >> D[i];
        f[0][0][0] = true;
        for (int i = 1; i <= n; i++)
            for (int j = i; j; j--)
                for (int d = 0; d <= 20 * j; d++)
                    for (int p = 0; p <= 20 * j; p++)
                        f[j][d][p] |= f[j - 1][d - D[i]][p - P[i]];
        int ansd = 0x3f3f3f3f, ansp = ~0x3f3f3f3f;
        for (int d = 0; d <= 20 * m; d++)
            for (int p = 0; p <= 20 * m; p++)
                if (f[m][d][p])
                {
                    if (abs(ansd - ansp) > abs(d - p))
                        ansd = d, ansp = p;
                    else if (abs(ansd - ansp) == abs(d - p) && d + p > ansd + ansp)
                        ansd = d, ansp = p;
                }
        cout << ansd << ' ' << ansp;
    }
}
namespace good
{
    constexpr int offset = 400;
    int p[N], d[N], f[M][2 * 20 * M];
    bool c[N][M][2 * 20 * M];

    void print(int i, int j, int k)
    {
        if (!j)
            return;
        if (c[i][j][k + offset])
            print(i - 1, j - 1, k - (d[i] - p[i])),
                cout << ' ' << i;
        else
            print(i - 1, j, k);
    }
    void solve()
    {
        for (int i = 1; i <= n; i++)
            cin >> p[i] >> d[i];

        memset(f, ~0x3f, sizeof(f));
        f[0][0 + offset] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = min(i, m); j; j--)
                for (int k = -20 * j; k <= 20 * j; k++)
                {
                    c[i][j][k + offset] = false;
                    if (k - (d[i] - p[i]) < -20 * j || k - (d[i] - p[i]) > 20 * j)
                        continue;
                    if (f[j][k + offset] < f[j - 1][k - (d[i] - p[i]) + offset] + d[i] + p[i])
                    {
                        f[j][k + offset] = f[j - 1][k - (d[i] - p[i]) + offset] + d[i] + p[i];
                        c[i][j][k + offset] = true;
                    }
                }
        int dlt = 1 << 30, sum = 0, dif = 0;
        for (int k = -20 * m; k <= 20 * m; k++)
        {
            if (f[m][k + offset] < 0)
                continue;
            if (abs(k) < dlt)
                dlt = abs(k), sum = f[m][k + offset], dif = k;
            else if (abs(k) == dlt && f[m][k + offset] > sum)
                sum = f[m][k + offset], dif = k;
        }
        cout << "Jury #" << ++T << '\n'
             << "Best jury has value " << ((sum - dif) >> 1) << " for prosecution and value " << ((sum + dif) >> 1) << " for defence:\n";
        print(n, m, dif);
        cout << "\n\n";
        /* Jury #1
           Best jury has value 6 for prosecution and value 4 for defence:
            2 3 */
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m, n || m)
        good::solve();
    return 0;
}