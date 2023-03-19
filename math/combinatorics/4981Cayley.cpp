// 对于n个不同的节点，能够组成的无根树的种数是 n^(n - 2)种
#include <bits/stdc++.h>
using namespace std;

const size_t p = 1e9 + 9;
size_t power(size_t n, size_t m)
{
    size_t ret = 1;
    while (m)
    {
        if (m & 1)
            ret = (ret * n) % p;
        n = (n * n) % p;
        m >>= 1;
    }
    return ret;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        size_t n;
        cin >> n;
        cout << power(n, n - 1) << endl;
    }
    return 0;
}
