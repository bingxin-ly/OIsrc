#include <bits/stdc++.h>
#define mod(_, _p) ((_ % _p + _p) % _p)
using namespace std;
typedef long long loong;

loong k, rs[11], ps[11];
void exgcd(loong a, loong b, loong &x, loong &y)
{
    if (!b)
        return x = 1, y = 0, void();
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}
loong CRT(int k)
{
    loong n = 1, ans = 0;
    for (int i = 1; i <= k; i++)
        n = n * ps[i];
    for (int i = 1; i <= k; i++)
    {
        loong m = n / ps[i], b, _;
        exgcd(m, ps[i], b, _); // b * m mod ps[i] = 1
        ans = (ans + (__int128)rs[i] * m * b % n) % n;
    }
    return mod(ans, n);
}

int main()
{
    cin >> k;
    for (int i = 1; i <= k; i++)
        cin >> rs[i];
    for (int i = 1; i <= k; i++)
        cin >> ps[i];
    for (int i = 1; i <= k; i++)
        mod(rs[i], ps[i]);
    cout << CRT(k);
    return 0;
}