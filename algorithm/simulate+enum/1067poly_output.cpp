#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k, f = 1;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> k;
        if (!k)
            continue;
        if (!f || k < 0)
            cout << (k > 0 ? '+' : '-');
        if (abs(k) != 1)
            cout << abs(k);
        cout << 'x', f = 0;
        if (n - i)
            cout << '^' << n - i + 1;
    }
    cin >> k;
    if (k)
        cout << (k > 0 && f != 1 ? "+" : "") << k << endl;
    return 0;
}