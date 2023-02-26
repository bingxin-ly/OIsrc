#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 10;
int f[MAX], d[MAX], n, minn, last;

int fa(int x)
{
    if (f[x] != x)
    {
        int last = f[x];
        f[x] = fa(f[x]);
        d[x] += d[last];
    }
    return f[x];
}
void check(int a, int b)
{
    int x = fa(a), y = fa(b);
    if (x != y)
    {
        f[x] = y;
        d[a] = d[b] + 1;
    }
    else
        minn = min(minn, d[a] + d[b] + 1);
    return;
}
int main()
{
    int i, t;
    cin >> n;
    for (i = 1; i <= n; i++)
        f[i] = i;
    minn = INT_MAX;
    for (i = 1; i <= n; i++)
    {
        cin >> t;
        check(i, t);
    }
    cout << minn;
    return 0;
}
