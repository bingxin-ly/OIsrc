#include <bits/stdc++.h>
using namespace std;

int n, a[400000], diff[400000];
bool fnd(int x)
{
    if (x + 2 <= n && diff[x + 2] + diff[x] >= 0)
        return true;
    else if (x - 2 >= 1 && diff[x - 2] + diff[x] >= 0)
        return true;
    else
        return false;
    return (x - 2 >= 1 && fnd(x - 2)) || (x + 2 <= n && fnd(x + 2));
}
int main()
{
    // freopen("sorting.in", "r", stdin);
    // freopen("sorting.out", "w", stdin);
    int t;
    cin >> t;
    while (t--)
    {
        memset(a, 0, sizeof(a));
        memset(diff, 0, sizeof(diff));
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        if (n & 1)
        {
            cout << "YES" << endl;
            continue;
        }

        for (int i = 1; i <= n; i++)
            diff[i] = a[i] - a[i - 1];

        bool ans = true;
        for (int i = 1; i <= n; i++)
            if (diff[i] < 0)
            {
                auto res = fnd(i);
                if (!res)
                    ans = false;
                break;
            }
        cout << (ans ? "YES" : "NO") << endl;
        n = 0;
    }
    return 0;
}