#include <algorithm>
#include <vector>
using std::vector;

vector<bool> dec2bin(int src)
{
    int quotient = src, remainder;
    vector<bool> ret;
    while (quotient)
        ret.push_back(remainder = quotient % 2),
            quotient /= 2;
    std::reverse(ret.begin(), ret.end());
    return ret;
}

size_t fast_pow(size_t a, int k)
{
    size_t result = 1;
    while (k)
    {
        if (k & 1)
            result *= a;
        a *= a;
        k >>= 1;
    }
    return result;
}

size_t fast_pow(size_t a, int k, int m)
{
    a %= m;
    size_t result = 1;
    while (k)
    {
        if (k & 1)
            result = result * a % m;
        a = a * a % m;
        k >>= 1;
    }
    return result;
}
