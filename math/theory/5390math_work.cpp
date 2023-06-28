#include <bits/stdc++.h>
using namespace std;

int power(int a, int b, int p = 998244353)
{
    int res = 1 % p;
    for (; b; b >>= 1)
    {
        if (b & 1)
            res = 1ll * res * a % p;
        a = 1ll * a * a % p;
    }
    return res;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, s = 0;
        cin >> n;
        for (int i = 1, x; i <= n; ++i)
            cin >> x, s |= x;
        cout << (1ll * s * power(2, n - 1) % 998244353) << '\n';
    }
    return 0;
}
