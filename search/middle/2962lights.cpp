#include <bits/stdc++.h>
using namespace std;

int n, m, ans = INT_MAX;
map<long long, int> f;
long long a[40];

int main()
{
    cin >> n >> m;
    a[0] = 1;
    for (int i = 1; i < n; ++i)
        a[i] = a[i - 1] * 2;

    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        a[u] |= ((long long)1 << v);
        a[v] |= ((long long)1 << u);
    }

    for (int i = 0; i < (1 << (n / 2)); ++i) // 1 / 2
    {
        long long t = 0;
        int cnt = 0;
        for (int j = 0; j < n / 2; ++j)
        {
            if ((i >> j) & 1)
            {
                t ^= a[j];
                ++cnt;
            }
        }
        if (!f.count(t))
            f[t] = cnt;
        else
            f[t] = min(f[t], cnt);
    }

    for (int i = 0; i < (1 << (n - n / 2)); ++i) // 1 / 2
    {
        long long t = 0;
        int cnt = 0;
        for (int j = 0; j < (n - n / 2); ++j)
        {
            if ((i >> j) & 1)
            {
                t ^= a[n / 2 + j];
                ++cnt;
            }
        }
        if (f.count((((long long)1 << n) - 1) ^ t))
            ans = min(ans, cnt + f[(((long long)1 << n) - 1) ^ t]);
    }

    cout << ans;
    return 0;
}
