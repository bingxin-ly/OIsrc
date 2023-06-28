#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        a.insert(upper_bound(a.begin(), a.end(), x), x);
        if (i % 2)
            cout << a[(i - 1) >> 1] << '\n';
    }
    return 0;
}