// C++ 17
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, ans = 0;
    cin >> n;
    for (int i = 1, tmp; i <= n; i++)
        cin >> tmp, ans = gcd(ans, tmp);
    cout << ans;
    return 0;
}