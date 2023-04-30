#include <bits/stdc++.h>
using namespace std;
int n, ans, p[400000];
int main()
{
    cin >> n;
    if (n == 1)
        cout << 0, exit(0);
    for (int i = 1; i <= n; ++i)
        p[i] = i;
    for (int i = 2; i <= n; ++i)
        if (p[i] == i)
            for (int j = i; j <= n; j += i)
                p[j] = p[j] * (i - 1) / i;
    for (int i = 1; i < n; ++i)
        ans += p[i];
    cout << (ans << 1 | 1) << endl;
    return 0;
}