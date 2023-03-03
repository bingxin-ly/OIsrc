#include <bits/stdc++.h>
using namespace std;

int main()
{
    size_t a, b, p;
    cin >> a >> b >> p;
    char s[30];
    sprintf(s, "%d^%d", a, b);
    a %= p;
    size_t result = 1;
    while (b)
    {
        if (b & 1)
            result = result * a % p;
        a = a * a % p;
        b >>= 1;
    }
    printf("%s mod %lld=%lld\n", s, p, result);
    return 0;
}