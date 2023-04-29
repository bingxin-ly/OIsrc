#include <bits/stdc++.h>
using namespace std;
typedef long long loong;

const loong N = 4e4, P = 999911658, ps[] = {0, 2, 3, 4679, 35617};
loong q, n;
loong rs[5], fac[N];
loong fpow(loong rs, loong k, int p)
{
    rs %= p;
    loong res = 1;
    while (k)
    {
        if (k & 1)
            res = res * rs % p;
        rs = rs * rs % p;
        k >>= 1;
    }
    return res;
}
loong C_(loong n, loong m, int p)
{
    if (m > n)
        return 0;
    return ((fac[n] * fpow(fac[m], p - 2, p)) % p * fpow(fac[n - m], p - 2, p) % p);
}
loong lucas(loong n, loong m, int p)
{
    if (n < m)
        return 0;
    if (!n)
        return 1;
    return C_(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}
loong CRT()
{
    loong ans = 0;
    for (loong i = 1; i <= 4; i++)
        ans = (ans + rs[i] * (P / ps[i]) % P * fpow(P / ps[i], ps[i] - 2, ps[i])) % P;
    return ans;
}

int main()
{
    cin >> n >> q;
    if (q % (P + 1) == 0)
        puts("0"), exit(0);
    for (loong i = 1; i <= 4; i++)
    {
        int p = ps[i];
        fac[0] = 1;
        for (loong j = 1; j <= p; j++)
            fac[j] = fac[j - 1] * j % p;
        for (loong d = 1, up = sqrt(n); d <= up; d++)
        {
            if (n % d)
                continue;
            rs[i] = (rs[i] + lucas(n, d, p)) % p;
            if (d * d != n)
                rs[i] = (rs[i] + lucas(n, n / d, p)) % p;
        }
    }
    cout << fpow(q, CRT(), P + 1) << endl;
    return 0;
}
