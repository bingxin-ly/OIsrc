#include <bits/stdc++.h>
#define int long long
using namespace std;

typedef pair<pair<int, int>, int> PIII;
map<PIII, int> mem;
int w(int a, int b, int c)
{
    if (mem.count({{a, b}, c}))
        return mem[{{a, b}, c}];
    int ans = 0;
    if (a <= 0 || b <= 0 || c <= 0)
        ans = 1;
    else if (a > 20 || b > 20 || c > 20)
        ans = w(20, 20, 20);
    else if (a < b && b < c)
        ans = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
    else
        ans = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
    mem[{{a, b}, c}] = ans;
    return ans;
}

signed main()
{
    int a, b, c;
    while (cin >> a >> b >> c)
    {
        if (a == b && b == c && c == -1)
            break;
        printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, w(a, b, c));
    }
    return 0;
}