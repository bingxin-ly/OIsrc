#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e7 + 50 + 100;
int f[N], nxt[N];

bool check(int x)
{
    while (x)
    {
        if (x % 10 == 7)
            return true;
        x /= 10;
    }
    return false;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int lst = 0;
    for (int i = 1; i <= 1e7 + 50; i++)
    {
        if (f[i])
            continue;
        if (check(i))
        {
            for (int j = i; j <= 1e7 + 50; j += i)
                f[j] = 1;
            continue;
        }
        nxt[lst] = i, lst = i;
    }
    int T;
    cin >> T;
    while (T--)
    {
        int x;
        cin >> x;
        if (f[x])
            cout << "-1\n";
        else
            cout << nxt[x] << '\n';
    }
    return 0;
}