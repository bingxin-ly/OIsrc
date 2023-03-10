#include <bits/stdc++.h>
using namespace std;

bool is_prime(size_t n)
{
    for (int i = 2, up = sqrt(n); i <= up; ++i)
        if (n % i == 0)
            return false;
    return true;
}
int main()
{
    size_t n, k;
    cin >> n >> k;
    n++, k++;
    if (is_prime(k) && n / k == 1)
        cout << 1;
    else
        cout << 2;
    return 0;
}