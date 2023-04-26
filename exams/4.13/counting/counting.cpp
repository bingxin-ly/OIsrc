#include <bits/stdc++.h>
using namespace std;

bool is_prime(int n)
{
    for (int i = 2, up = sqrt(n); i <= up; i++)
        if (n % i == 0)
            return false;
    return true;
}
int main()
{
    freopen("counting.in","r",stdin);
    freopen("counting.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 1, tmp, up = 2 * n; i <= up; i++)
    {
        cin >> tmp;
        if (!is_prime(tmp))
            cout << 0 << endl, exit(0);
    }
}