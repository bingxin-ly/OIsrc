#include <bits/stdc++.h>
using namespace std;

void exgcd(int a, int b, int &x, int &y)
{
    if (!b)
        return x = 1, y = 0, void();
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

int main()
{
    int x, y;
    exgcd(6, 9, x, y);
    cout << x << ' ' << y << endl;
    return 0;
}