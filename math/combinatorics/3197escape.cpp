#include <bits/stdc++.h>
using namespace std;
const int p = 1e5 + 3;
int fast_pow(size_t x, size_t k)
{
    x %= p;
    k %= p - 1;
    size_t res = 1;
    while (k)
    {
        if (k & 1)
            res = res * x % p;
        x = x * x % p;
        k >>= 1;
    }
    return res;
}

int main()
{
    size_t m, n;
    cin >> m >> n;
    // 取模之后可能被减数小于减数！！！
    cout << (fast_pow(m, n) - (m * fast_pow(m - 1, n - 1)) % p + p) % p;
    return 0;
}