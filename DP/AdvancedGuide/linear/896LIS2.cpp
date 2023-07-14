#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, a[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> s;
    s.emplace_back(a[1]);

    for (int i = 2; i <= n; i++)
        if (a[i] > s.back())
            s.emplace_back(a[i]);
        else
            *lower_bound(s.begin(), s.end(), a[i]) = a[i];
    cout << s.size();
    return 0;
}