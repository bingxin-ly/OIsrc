#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        int n, k;
        cin >> n >> k;
        int x = k, y = n - k;
        if (x % y == k && x >= 0 && y > 0)
            cout << x << ' ' << y << '\n';
        else
            cout << "-1\n";
    }
    return 0;
}