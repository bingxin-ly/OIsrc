#include <bits/stdc++.h>
using namespace std;

int a[100005];
unordered_map<int, int> mem;
signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, v, f = 0;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        if (n > 20)
        {
            cout << "Yes\n";
            continue;
        }
        for (int i = 0; i < 1 << n; i++)
        {
            v = 0;
            for (int j = 0; j < n; j++)
                if (i & (1 << j))
                    v += a[j + 1];
                else
                    v -= a[j + 1];
            if (++mem[v] >= 2)
            {
                f = 1;
                cout << "Yes\n";
                break;
            }
        }
        if (!f)
            cout << "No\n";
        mem.clear();
    }
    return 0;
}