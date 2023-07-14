#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int m, s, t;
    cin >> m >> s >> t;
    int s1 = 0, s2 = 0;
    for (int i = 1; i <= t; i++)
    {
        s1 += 17;
        if (m >= 10)
            s2 += 60, m -= 10;
        else
            m += 4;
        if (s2 > s1)
            s1 = s2;
        if (s1 > s)
            cout << "Yes\n"
                 << i,
                exit(0);
    }
    cout << "No\n"
         << s1;
    return 0;
}