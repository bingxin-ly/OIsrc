#include <bits/stdc++.h>
using namespace std;

int main()
{
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    if (r1 == r2 && c1 == c2) // special
    {
        puts("0 0 0");
        return 0;
    }

    int dx = abs(r1 - r2), dy = abs(c1 - c2);

    {
        cout << (bool)dx + (bool)dy << ' ';
    }
    {
        int k1 = r1 - c1, s1 = r1 + c1;
        int k2 = r2 - c2, s2 = r2 + c2;
        if (((k1 - k2) % 2) || (s1 - s2) % 2)
            cout << "0 ";
        else if (k1 == k2 || s1 == s2)
            cout << "1 ";
        else
            cout << "2 ";
    }
    {
        cout << max(dx, dy) << endl;
    }
    return 0;
}