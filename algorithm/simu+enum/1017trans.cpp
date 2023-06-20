#include <iostream>
#include <cstdio>
using namespace std;
char z[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
void trans(int n, int m)
{
    if (n == 0)
        return;
    if (n > 0 || n % m == 0)
    {
        trans(n / m, m);
        cout << z[n % m];
    }
    else
    {
        trans(n / m + 1, m);
        cout << z[-m + n % m];
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    cout << n << '=';
    trans(n, m);
    cout << "(base" << m << ')';
    return 0;
}