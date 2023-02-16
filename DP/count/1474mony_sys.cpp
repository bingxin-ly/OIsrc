#include <bits/stdc++.h>
#define int ssize_t
using namespace std;

const int MAX = 1e4 + 10;
int v, n, mo[30], f[MAX];

signed main()
{
    cin >> v >> n;
    for (int i = 1; i <= v; i++)
        cin >> mo[i];
    f[0] = 1;
    for (int i = 1; i <= v; i++)
        for (int j = mo[i]; j <= n; j++)
            f[j] += f[j - mo[i]];
    cout << f[n] << endl;
    return 0;
}