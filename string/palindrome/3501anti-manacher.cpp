#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 5;
int n, m, R[N << 1];
char s[N], t[N << 1];
signed main()
{
    scanf("%d%s", &n, s + 1);
    t[++m] = '@';
    for (int i = 1; i <= n; i++)
        t[++m] = s[i], t[++m] = '@';

    int c = 0, r = 0;
    long long cnt = 0;
    for (int i = 3; i < m; i += 2)
    {
        R[i] = i <= r ? min(R[2 * c - i], r - i + 1) : 0;
        while (t[i - R[i] - 1] + t[i + R[i] + 1] == '0' + '1')
            R[i] += 2;
        cnt += R[i] >> 1;
        if (r < i + R[i] - 1)
            r = i + R[i] - 1, c = i;
    }
    cout << cnt;
    return 0;
}