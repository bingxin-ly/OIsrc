#include <bits/stdc++.h>
using namespace std;

const int MAX = 2.5e4 + 10;
int T, n, mo[110], f[MAX], ans;

int main()
{
    cin >> T;
    while (T--)
    {
        memset(f, 0, sizeof(f));
        cin >> n;
        ans = n;
        for (int i = 1; i <= n; i++)
            cin >> mo[i];
        sort(mo + 1, mo + n + 1);
        f[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            if (f[mo[i]])
            {
                ans--;
                continue;
            }
            for (int j = mo[i]; j <= mo[n]; j++)
                f[j] = f[j] | f[j - mo[i]];
        }
        cout << ans << endl;
    }
    return 0;
}