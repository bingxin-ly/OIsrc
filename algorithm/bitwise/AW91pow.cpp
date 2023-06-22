// AcWing 91
#include <bits/stdc++.h>
using namespace std;

int power(int a, int b, int p)
{
    int res = 1;
    for (; b; b >>= 1)
    {
        if (b & 1)
            res = 1ll * res * a % p;
        a = 1ll * a * a % p;
    }
    return res;
}

signed main()
{
    int a, b, p;
    cin >> a >> b >> p;
    cout << power(a, b, p);
    return 0;
}