#include <bits/stdc++.h>
using namespace std;

ssize_t a[(int)1e5];
int p;
ssize_t pow(ssize_t x, int k)
{
    x %= p;
    ssize_t ans = 1;
    for (int i = k; i; i >>= 1, x = x * x % p)
        if (i & 1)
            ans = ans * x % p;
    return ans;
}
ssize_t C(ssize_t n, ssize_t m)
{
    if (m > n)
        return 0;
    // 由费马小定理，当模数 p为质数时，b的乘法逆元为 b^(p-2)
    return ((a[n] * pow(a[m], p - 2)) % p * pow(a[n - m], p - 2) % p);
}
ssize_t Lucas(ssize_t n, ssize_t m)
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
        a[0] = 1;
        for (int i = 1; i <= p; i++) // 预处理阶乘
            a[i] = (a[i - 1] * i) % p;
        cout << Lucas(n + m, n) << endl;
    }
    return 0;
}
