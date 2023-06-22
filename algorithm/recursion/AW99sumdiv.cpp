#include <bits/stdc++.h>
using namespace std;

const int MOD = 9901;
int power(int a, int b, int p = MOD)
{
    int res = 1;
    for (a %= p; b; b >>= 1)
    {
        if (b & 1)
            res = 1ll * res * a % p;
        a = 1ll * a * a % p;
    }
    return res;
}
signed math()
{
    int a, b, res = 1;
    cin >> a >> b;
    if (!a) // 特判
        return cout << 0, 0;
    for (int p = 2, up = sqrt(a); p <= up; p++)
        if (a % p == 0)
        {
            int c = 0;
            while (a % p == 0)
                c += 1, a /= p;
            // p_i ^ c_i, q = p, n = b * c + 1
            if ((p - 1) % MOD == 0) // 还需要特判逆元不存在的情况
                (res *= b * c + 1) %= MOD;
            /* 由于 p - 1的是模数的倍数, 故 p % mod = 1
               所以1 + p + ... + p^k每个数 %MOD 都是 1，总共就是 k + 1 */
            else
                (res *= (power(p, b * c + 1) - 1) * power(p - 1, MOD - 2) % MOD) %= MOD;
        }
    if (a != 1)
    {
        if ((a - 1) % MOD == 0)
            (res *= b + 1) %= MOD;
        else
            (res *= (power(a, b + 1) - 1) * power(a - 1, MOD - 2) % MOD) %= MOD;
    }
    cout << (res + MOD) % MOD;
    return 0;
}

// 使用分治法求 sum(p, c) = p^0 + p^1 + p^2 + ... + p^c
int sum(int p, int c)
{
    if (!c)
        return 1;
    if (c & 1)
        return (1 + power(p, (c + 1) >> 1)) * sum(p, (c - 1) >> 1) % MOD;
    else
        return ((1 + power(p, c >> 1)) * sum(p, (c >> 1) - 1) + power(p, c)) % MOD;
}
signed DAC()
{
    int a, b, res = 1;
    cin >> a >> b;
    if (!a)
        return cout << 0, 0;
    for (int p = 2, up = sqrt(a); p <= up; p++)
        if (a % p == 0)
        {
            int c = 0;
            while (a % p == 0)
                c += 1, a /= p;
            (res *= sum(p, b * c)) %= MOD;
        }
    if (a != 1)
        (res *= sum(a, b)) %= MOD;
    cout << res;
    return 0;
}