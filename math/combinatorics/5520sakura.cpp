#include <bits/stdc++.h>
using namespace std;

ssize_t ans = 1, n, m, p;

int main()
{
    cin >> n >> n >> m >> p;
    for (int i = n - m + 1; i >= n - 2 * m + 2; i--)
        ans = (ans * i) % p;
    cout << ans;
    return 0;
}
