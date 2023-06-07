#include <bits/stdc++.h>
using namespace std;

int n, a[105], b[105];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> a[1] >> b[1];
    for (int i = 2; i <= n; i++)
    {
        cin >> a[i] >> b[i];
        while (a[i])
            if (abs(a[1]) < abs(a[i]))
                swap(a[1], a[i]), swap(b[1], b[i]);
            else
                b[1] -= b[i] * (a[1] / a[i]), a[1] %= a[i];
        if (i > 2)
            b[2] = __gcd(b[2], b[i]), b[1] %= b[2];
    }
    cout << a[1] << ' ' << b[1] << '\n'
         << a[2] << ' ' << b[2];
    return 0;
}