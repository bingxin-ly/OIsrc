#include <bits/stdc++.h>
using namespace std;
int fast_pow(size_t a, int k, int m)
{
    a %= m;
    size_t res = 1;
    while (k)
    {
        if (k & 1)
            res = res * a % m;
        a = a * a % m;
        k >>= 1;
    }
    return res;
}

int main()
{
    int a, b, p;
    cin >> a >> b >> p;
    printf("%d^%d mod %d=%d\n", a, b, p, fast_pow(a, b, p));
    return 0;
}