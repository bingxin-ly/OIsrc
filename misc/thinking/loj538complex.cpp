#include <bits/stdc++.h>
using namespace std;

constexpr int M = 1e5 + 5;
int n, m, k, s[M];
long long a[200];

void forcemono(int lim, int &x, int &y)
{
    for (int i = 2; i < lim; i++)
        a[i] = k * a[i - 1] + a[i - 2];
    for (int i = 2; i <= m && s[i] < lim; i++)
    {
        if (a[s[i]] > a[s[x]])
            x = i;
        if (a[s[i]] < a[s[y]])
            y = i;
    }
    if (s[m] >= lim)
        a[lim - 1] + a[lim - 2] > 0 ? x = m : y = m;
}
signed main()
{
    freopen("C:\\Users\\Pai\\Downloads\\seq7.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m;
    for (int i = 1; i <= m; i++)
        cin >> s[i];
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x = 1, y = 1;
        cin >> a[0] >> a[1] >> k;
        if (!a[0] && !a[1])
            ;
        else if (a[0] * a[1] >= 0)
            forcemono(4, x, y);
        else if (abs(a[0]) <= abs(a[1]))
            forcemono(5, x, y);
        else
        {
            int lim;
            for (lim = 2; abs(a[lim - 1]) < max(abs(a[0]), abs(a[1])); lim++)
                a[lim] = k * a[lim - 1] + a[lim - 2];
            for (int j = 2; j <= m && s[j] < lim; j++)
            {
                if (a[s[j]] > a[s[x]])
                    x = j;
                if (a[s[j]] < a[s[y]])
                    y = j;
            }
            if (s[m] >= lim)
                k *a[lim - 1] + a[lim - 2] > 0 ? x = m : y = m;
        }
        cout << s[x] << ' ' << s[y] << '\n';
    }
    return 0;
}