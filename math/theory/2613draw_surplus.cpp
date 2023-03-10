#include <bits/stdc++.h>
#define mod(_, _p) ((_ % _p + _p) % _p)
using namespace std;

const int p = 19260817;
inline void read(ssize_t &n)
{
    int res = 0, ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        res = (res << 3) + (res << 1) + (ch - '0');
        res %= p; // 直接对MOD取余
        ch = getchar();
    }
    n = res;
}
void exgcd(int a, int b, ssize_t &x, ssize_t &y)
{
    if (!b)
        return x = 1, y = 0, void();
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

int main()
{
    ssize_t a, b, x, y;
    read(a), read(b);
    if (!b)
        return puts("Angry!"), 0;
    exgcd(b, p, x, y);
    cout << a * mod(x, p) % p << endl;
    return 0;
}