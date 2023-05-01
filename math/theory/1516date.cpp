#include <bits/stdc++.h>
using namespace std;
typedef long long loong;

loong exgcd(loong a, loong b, loong &x, loong &y)
{
    if (!b)
        return x = 1, y = 0, a;
    int gcd = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return gcd;
}

int main()
{
    loong x, y, m, n, l;
    cin >> x >> y >> m >> n >> l;
    loong a = n - m, b = l, c = x - y, xx, yy;
    if (a < 0)
        a *= -1, c *= -1;
    loong g = exgcd(a, b, xx, yy);
    if (c % g)
        puts("Impossible");
    else
    {
        int mod = b / g;
        cout << (c / g * xx % mod + mod) % mod << endl;
    }
    return 0;
}
