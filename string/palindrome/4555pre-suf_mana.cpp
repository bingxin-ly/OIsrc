#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, R[N << 1], ed[N], st[N];
char s[N], t[N << 1];
signed main()
{
    scanf("%s", s + 1), n = strlen(s + 1);
    t[0] = '!';
    for (int i = 1; i <= n; i++)
        t[++m] = '#', t[++m] = s[i];
    t[++m] = '#', t[++m] = '@';

    int c = 0, r = 0;
    for (int i = 1; i < m; i++)
    {
        R[i] = i <= r ? min(R[2 * c - i], r - i + 1) : 1;
        while (t[i - R[i]] == t[i + R[i]])
            R[i] += 1;
        if (r < i + R[i] - 1)
        {
            for (int j = r + 1; j <= i + R[i] - 1; j++)
                if (t[j] != '#')
                    ed[j >> 1] = j - i + 1;
            r = i + R[i] - 1, c = i;
        }
    }
    c = m, r = m;
    for (int i = m - 1; i; i--)
    {
        R[i] = i >= r ? min(R[2 * c - i], i - r + 1) : 1;
        while (t[i - R[i]] == t[i + R[i]])
            R[i] += 1;
        if (r > i - R[i] + 1)
        {
            for (int j = i - R[i] + 1; j < r; j++)
                if (t[j] != '#')
                    st[j >> 1] = i - j + 1;
            r = i - R[i] + 1, c = i;
        }
    }
    int ans = 0;
    for (int i = 1; i < n; i++)
        ans = max(ans, ed[i] + st[i + 1]);
    cout << ans;
    return 0;
}