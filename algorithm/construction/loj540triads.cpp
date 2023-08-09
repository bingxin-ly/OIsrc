#include <bits/stdc++.h>
using namespace std;

constexpr int N = 505;
int n, m, s, c[N], r[N], w[N][N];

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    c[3] = 1;
    for (int i = 4; i <= 500; i++)
        c[i] = c[i - 1] + (i - 1) * (i - 2) / 2;
    cin >> n;
    while (n)
    {
        int p = upper_bound(c + 3, c + 500 + 1, n) - c - 1;
        r[++m] = p, s += p, n -= c[p];
    }
    cout << s << '\n';
    for (int i = 1, o = 0; i <= m; i++)
    {
        o += r[i - 1];
        for (int j = o + 1; j < o + r[i]; j++)
            for (int k = j + 1; k <= o + r[i]; k++)
                w[j][k] = 1;
    }
    for (int i = 1; i < s; i++)
    {
        for (int j = i + 1; j <= s; j++)
            cout << w[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}