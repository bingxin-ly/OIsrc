// C++ 17
#include <bits/stdc++.h>
using namespace std;
typedef __int128 lt;

lt x, y, d;
void exgcd(lt a, lt b, lt &x, lt &y)
{
    if (!b)
        d = a, x = 1, y = 0;
    else
        exgcd(b, a % b, y, x), y -= a / b * x;
}
// __int128的gcd / lcm要自己写！！
lt gcd(lt a, lt b)
{
    return b ? gcd(b, a % b) : a;
}
lt lcm(lt a, lt b)
{
    return a / gcd(a, b) * b;
}
lt a, b, A, B;
void merge()
{
    exgcd(a, A, x, y);
    lt c = B - b;
    if (c % d)
        puts("-1"), exit(0);
    x = x * c / d % (A / d);
    if (x < 0)
        x += A / d;
    lt mod = lcm(a, A);
    b = (a * x + b) % mod;
    if (b < 0)
        b += mod;
    a = mod;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        ssize_t _A, _B;
        cin >> _A >> _B;
        A = _A, B = _B;
        if (i > 1)
            merge();
        else
            a = A, b = B;
    }
    cout << (long long)(b % a) << endl;
    return 0;
}