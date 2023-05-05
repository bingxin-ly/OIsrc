#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

ull p[64];
void insert(ull x)
{
    for (int i = 63; ~i; i--)
    {
        if (!(x >> i))
            continue;
        if (!p[i])
        {
            p[i] = x;
            break;
        }
        x ^= p[i];
    }
}

int main()
{
    int n;
    cin >> n;
    for (ull i = 1, a; i <= n; i++)
        cin >> a, insert(a);

    ull ans = 0;
    for (int i = 63; ~i; i--)
        ans = max(ans, ans ^ p[i]);
    cout << ans;
    return 0;
}