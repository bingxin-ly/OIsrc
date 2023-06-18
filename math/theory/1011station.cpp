#include <bits/stdc++.h>
using namespace std;

int fib[20], bus[30];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int a, n, m, x;
    cin >> a >> n >> m >> x;
    fib[2] = fib[3] = 1;
    for (int i = 4; i <= n; i++)
        fib[i] = fib[i - 2] + fib[i - 1];

    for (int i = 3; i < n; i++)
        bus[i] = bus[i - 1] + fib[i - 2];
    int u = (m - a * (n - 3)) / bus[n - 1];

    if (x <= 2)
        cout << a;
    else
        cout << bus[x] * u + (x - 2) * a;
    return 0;
}