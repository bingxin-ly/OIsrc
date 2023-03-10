#include <bits/stdc++.h>
#define mod(_, _p) ((_ % _p + _p) % _p)
using namespace std;
int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
        return x = 1, y = 0, a;
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
bool solve(int a, int b, int c, int &x, int &y)
{
    int d = exgcd(a, b, x, y);
    if (c % d)
        return false;
    int k = c / d;
    x *= k, y *= k;
    return true;
}

int main()
{
    int a, b, x, y;
    cin >> a >> b;
    solve(a, b, 1, x, y);
    cout << mod(x, b);
    return 0;
}