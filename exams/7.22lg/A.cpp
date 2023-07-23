#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    char ch;
    int a = 0, b = 0, c = 0;
    while (cin >> ch)
        if (isdigit(ch))
            a++;
        else if (islower(ch))
            b++;
        else if (isupper(ch))
            c++;
    cout << a << ' ' << b << ' ' << c;
    return 0;
}