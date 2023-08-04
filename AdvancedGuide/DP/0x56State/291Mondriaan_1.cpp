#include <bits/stdc++.h>
using namespace std;

int n, m, vad[1 << 11];
long long f[12][1 << 11];

bool check(int i)
{
    bool odd = false;
    for (int j = 0; j < m; j++)
        if (!(i & 1 << j))
            odd ^= 1;
        else if (odd)
            return false;
    return !odd;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m, n || m)
    {
        for (int i = 0; i < 1 << m; i++)
            vad[i] = check(i);
        f[0][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < 1 << m; j++)
            {
                f[i][j] = 0;
                for (int k = 0; k < 1 << m; k++)
                    if (!(j & k) && vad[j | k])
                        f[i][j] += f[i - 1][k];
            }
        cout << f[n][0] << '\n';
    }
    return 0;
}