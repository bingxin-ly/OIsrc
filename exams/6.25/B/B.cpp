#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        cout << (n % 3 != 2 ? "Acestar\n" : "Blueqwq\n");
    }
    return 0;
}