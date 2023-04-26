#include <bits/stdc++.h>
typedef long long loong;
using namespace std;

const int MOD = 1e9 + 7;
loong n, m, ans, f[30], inv[30];
loong C(loong n, loong m)
{
    if (n < 0 || m < 0 || n < m)
        return 0;
    if (n % MOD == 0 || m == 0)
        return 1;
    loong res = 1;
    for (loong i = n - m + 1; i <= n; ++i)
        res *= (i % MOD), res %= MOD;
    for (int i = 1; i <= m; ++i)
        res *= inv[i], res %= MOD;
    return res;
}

loong qpow(loong b, loong t)
{
    loong res = 1;
    while (t > 0)
    {
        if (t & 1)
            res = (res * b) % MOD;
        b = (b * b) % MOD;
        t >>= 1;
    }
    return res;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> f[i];
    for (int i = 1; i <= 20; ++i)
        inv[i] = qpow(i, MOD - 2);

    ans = C(n + m - 1, n - 1);
    for (int x = 1; x < 1 << n; x++)
    {
        loong t = n + m, p = 0;
        for (int i = 0; i < n; i++)
            if ((1 << i) & x)
                p++, t -= f[i + 1];
        t -= p + 1;
        if (p & 1)
            ans -= C(t, n - 1), ans %= MOD;
        else
            ans += C(t, n - 1), ans %= MOD;
    }
    cout << (ans + MOD) % MOD << endl;
    return 0;
}
