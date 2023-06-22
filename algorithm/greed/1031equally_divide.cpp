#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    int c = 0, s = 0, a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i], c += a[i];
    int avg = c / n;
    for (int i = 0; i < n; i++)
        a[i] -= avg;
    for (int i = 0; i < n; i++)
        if (a[i])
            a[i + 1] += a[i], s += 1;
    cout << s;
    return 0;
}