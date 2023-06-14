#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    long long ans = 0;
    for (int i = 1;; i++)
    {
        ans += i;
        if (ans > n)
        {
            ans -= i;
            int a = n % ans, b = i + 1 - a;
            if (!a)
                a += 1, b -= 2;
            if (i % 2)
                swap(a, b);
            cout << a << '/' << b << endl;
            break;
        }
    }
    return 0;
}