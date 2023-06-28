#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5;
int n, o[N], d[N], q[N], ans[N];
long long s[N];

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> o[i] >> d[i];

    for (int i = 1; i <= n; i++)
        s[i] = s[i + n] = o[i] - d[i];
    for (int i = 1; i <= n << 1; i++)
        s[i] += s[i - 1];

    int hh = 0, tt = -1;
    for (int i = n << 1; i; i--)
    {
        if (hh <= tt && q[hh] >= i + n)
            hh++;
        while (hh <= tt && s[q[tt]] >= s[i])
            tt--;
        q[++tt] = i;
        if (i <= n && s[q[hh]] >= s[i - 1])
            ans[i] |= 1;
    }

    d[0] = d[n];
    for (int i = 1; i <= n; i++)
        s[i] = s[i + n] = o[i] - d[i - 1];
    for (int i = 1; i <= n << 1; i++)
        s[i] += s[i - 1];

    hh = 0, tt = -1;
    for (int i = 1; i <= n << 1; i++)
    {
        if (hh <= tt && q[hh] < i - n)
            hh++;
        if (i > n && s[q[hh]] <= s[i])
            ans[i - n] |= 1;
        while (hh <= tt && s[q[tt]] <= s[i])
            tt--;
        q[++tt] = i;
    }

    for (int i = 1; i <= n; i++)
        cout << (ans[i] ? "TAK\n" : "NIE\n");
    return 0;
}