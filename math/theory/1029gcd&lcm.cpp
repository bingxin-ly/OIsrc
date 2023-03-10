// C++ 17
#define __cplusplus 201703L
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int x, y, cnt = 0;
    cin >> x >> y;
    int mul = x * y;
    for (int i = x, up = sqrt(mul); i <= up; i++)
    {
        if (mul % i)
            continue;
        if (gcd(i, mul / i) == x)
            cnt += i == mul / i ? 1 : 2;
    }
    cout << cnt << endl;
    return 0;
}