#include <bits/stdc++.h>
using namespace std;
typedef long long loong;

loong fac[(int)1e5];
int p;
loong pow(loong x, int k)
{
    x %= p;
    loong ans = 1;
    for (int i = k; i; i >>= 1, x = x * x % p)
        if (i & 1)
            ans = ans * x % p;
    return ans;
}
loong C(loong n, loong m)
{
    if (m > n)
        return 0;
    // 由费马小定理，当模数 p为质数时，b的乘法逆元为 b^(p-2)
    return ((fac[n] * pow(fac[m], p - 2)) % p * pow(fac[n - m], p - 2) % p);
}
loong Lucas(loong n, loong m)
{
    if (!m)
        return 1;
    return C(n % p, m % p) * Lucas(n / p, m / p) % p;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m >> p;
        fac[0] = 1;
        for (int i = 1; i <= p; i++) // 预处理阶乘
            fac[i] = (fac[i - 1] * i) % p;
        cout << Lucas(n + m, n) << endl;
    }
    return 0;
}
