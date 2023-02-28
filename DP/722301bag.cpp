#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

long long a[1000086];

long long binpow(long long b, long long p, long long k)
{
    b %= k;
    long long res = 1;
    while (p > 0)
    {
        if (p & 1)
            res = res * b % k;
        b = b * b % k;
        p >>= 1;
    }
    return res;
}

int main()
{
    long long n, p;
    long long ans = 1;
    scanf("%lld%lld", &n, &p);
    for (long long i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (long long i = 1; i <= n; i++)
    {
        ans *= (binpow(p, a[i], mod) % mod + 1);
        ans %= mod;
    }
    printf("%lld", ans % mod);
    return 0;
}