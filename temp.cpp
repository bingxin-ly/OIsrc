#include <bits/stdc++.h>
using namespace std;

map<int, long long> fac = {{0, 1}, {1, 1}};
long long get_fac(int n)
{
    if (n < 0)
        return -1;
    if (fac.count(n))
        return fac[n];
    int lastn = fac.crbegin()->first;
    long long lastv = fac.crbegin()->second;
    for (int i = lastn + 1; i <= n; i++)
        lastv *= i, fac[i] = lastv;
    return lastv;
}
int main()
{
    int n;
    while (cin >> n)
        cout << get_fac(n) << endl;
    return 0;
}
